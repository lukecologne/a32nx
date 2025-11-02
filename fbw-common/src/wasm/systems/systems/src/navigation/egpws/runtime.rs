use std::{fmt::Debug, time::Duration};

use uom::si::{
    angle::degree,
    f64::{Angle, Ratio, Velocity},
    length::foot,
    ratio::ratio,
    velocity::{foot_per_minute, knot},
};

use crate::{
    navigation::{
        adirs::{AirDataReferenceBus, InertialReferenceBus},
        ils::InstrumentLandingSystemBus,
        radio_altimeter::RadioAltimeter,
        taws::{
            TerrainAwarenessWarningSystemBusOutputs, TerrainAwarenessWarningSystemDiscreteInputs,
            TerrainAwarenessWarningSystemDiscreteOutputs,
        },
    },
    shared::{
        derivative::DerivativeNode,
        interpolation,
        logic_nodes::{ConfirmationNode, MonostableTriggerNode},
        low_pass_filter::LowPassFilter,
        rate_lmiter::RateLimiter,
    },
    simulation::UpdateContext,
};

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub(super) enum FlightPhase {
    Takeoff,
    Approach,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
#[allow(dead_code)]
pub enum AuralWarning {
    None,
    PullUp,
    Terrain,
    TooLowTerrain,
    TooLowGear,
    TooLowFlaps,
    SinkRate,
    DontSink,
    GlideslopeSoft,
    GlideslopeHard,
    TerrainAhead,
    ObstacleAhead,
}
impl AuralWarning {
    /// Gets the duration corresponding to the aural warning. The duration is of a full cycle,
    /// so the length of the message, plus any silence after it.
    fn get_duration(&self) -> Duration {
        match self {
            AuralWarning::None => Duration::from_secs(0),
            AuralWarning::PullUp => Duration::from_secs_f64(1.1),
            AuralWarning::Terrain => Duration::from_secs_f64(2.4),
            AuralWarning::TooLowTerrain => Duration::from_secs_f64(1.1),
            AuralWarning::TooLowGear => Duration::from_secs_f64(1.1),
            AuralWarning::TooLowFlaps => Duration::from_secs_f64(1.1),
            AuralWarning::SinkRate => Duration::from_secs_f64(1.1),
            AuralWarning::DontSink => Duration::from_secs_f64(1.1),
            AuralWarning::GlideslopeSoft => Duration::from_secs_f64(1.6),
            AuralWarning::GlideslopeHard => Duration::from_secs_f64(1.6),
            AuralWarning::TerrainAhead => Duration::from_secs_f64(2.4),
            AuralWarning::ObstacleAhead => Duration::from_secs_f64(2.4),
        }
    }
}

#[derive(Default, Clone, Copy, Debug)]
pub struct EnhancedGroundProximityWarningComputerPinProgramming {
    pub audio_declutter_disable: bool,
    pub alternate_lamp_format: bool,
}

pub(super) struct EnhancedGroundProximityWarningComputerRuntime {
    /// Pin programming settings. Read only once at computer startup.
    pin_programs: EnhancedGroundProximityWarningComputerPinProgramming,
    /// If non-Duration::ZERO, the remaining time the runtime needs to initialize itself. Otherwise
    /// the self-check has been completed.
    remaining_startup: Duration,

    reposition_mode_confirm_node: ConfirmationNode,

    /// The on ground and flight phase state is saved in NVM
    on_ground: bool,
    flight_phase: FlightPhase,

    // General Inputs
    chosen_vertical_speed_ft_min: f64,
    chosen_altitude_ft: f64,
    ra_ft: f64,

    // On ground/phase helpers
    ground_to_air_confirm_node: ConfirmationNode,
    takeoff_to_approach_condition_integrator: f64,

    // General GPWS Fault logic
    gpws_sys_fault: bool,
    terr_sys_fault: bool,
    gs_fault: bool,
    vs_fault: bool,
    altitude_fault: bool,

    audio_inhibit_discrete_conf_node: ConfirmationNode,
    gpws_inhibit_discrete_conf_node: ConfirmationNode,

    // GPWS Mode 1 Logic
    mode_1_sinkrate_conf_node_1: ConfirmationNode,
    mode_1_sinkrate_conf_node_2: ConfirmationNode,
    mode_1_pull_up_conf_node_1: ConfirmationNode,
    mode_1_pull_up_conf_node_2: ConfirmationNode,
    mode_1_sinkrate_time_to_impact_min: f64,
    mode_1_sinkrate_emitted_for_current_time_to_impact: bool,

    mode_1_sinkrate_lamp_active: bool,
    mode_1_sinkrate_voice_active: bool,
    mode_1_pull_up_active: bool,

    // GPWS Mode 2 Logic
    mode_2_takeoff_latch_node: MonostableTriggerNode,
    mode_2_closure_rate_derivative: DerivativeNode<f64>,
    mode_2_ra_rate_limiter: RateLimiter<f64>,
    mode_2_closure_rate_rate_limiter: RateLimiter<f64>,
    mode_2_ra_filter: LowPassFilter<f64>,

    mode_2_pull_up_preface_voice_emitted: bool,
    mode_2_pull_up_preface_active: bool,
    mode_2_pull_up_active: bool,
    mode_2_terrain_active: bool,

    // GPWS Mode 3 Logic
    mode_3_max_achieved_alt_ft: f64,

    mode_3_lamp_active: bool,
    mode_3_dont_sink_voice_active: bool,

    // GPWS Mode 4 Logic
    mode_4_too_low_gear_voice_active: bool,
    mode_4_too_low_flaps_voice_active: bool,
    mode_4_too_low_terrain_voice_active: bool,

    // GPWS Mode 5 Logic
    mode_5_time_to_next_aural: Duration,
    mode_5_declutter_threshold_increase: f64,
    mode_5_glideslope_soft_voice_active: bool,
    mode_5_glideslope_hard_voice_active: bool,
    mode_5_glideslope_lamp_active: bool,

    // Aural output management
    number_of_aural_warning_emissions: u32,
    time_since_first_emission: Duration,

    // General outputs
    warning_lamp_activated: bool,
    alert_lamp_activated: bool,
    aural_output: AuralWarning,
}

impl EnhancedGroundProximityWarningComputerRuntime {
    // These need to be ordered in ascending order for the interpolation function to work
    const MODE_1_ALERT_AREA_BREAKPOINTS: [f64; 2] = [-5007., -964.];
    const MODE_1_ALERT_AREA_VALUES: [f64; 2] = [2450., 10.];
    const MODE_1_WARNING_AREA_BREAKPOINTS: [f64; 3] = [-7125., -1710., -1482.];
    const MODE_1_WARNING_AREA_VALUES: [f64; 3] = [2450., 284., 10.];

    const MODE_2_ALERT_AREA_BREAKPOINTS: [f64; 3] = [2038., 3545., 9800.];
    const MODE_2_ALERT_AREA_VALUES: [f64; 3] = [30., 1220., 2450.];
    const MODE_2_B_CUTOFF_AREA_BREAKPOINTS: [f64; 2] = [-1000., -400.];
    const MODE_2_B_CUTOFF_AREA_VALUES: [f64; 2] = [600., 200.];

    const MODE_3_ALERT_AREA_BREAKPOINTS: [f64; 2] = [8., 143.];
    const MODE_3_ALERT_AREA_VALUES: [f64; 2] = [30., 1500.];

    const MODE_5_SOFT_ALERT_UPPER_BOUNDARY_BREAKPOINTS: [f64; 2] = [-500., 0.];
    const MODE_5_SOFT_ALERT_UPPER_BOUNDARY_VALUES: [f64; 2] = [1000., 500.];
    const MODE_5_SOFT_ALERT_BREAKPOINTS: [f64; 2] = [1.3, 2.7];
    const MODE_5_SOFT_ALERT_VALUES: [f64; 2] = [150., 50.];
    const MODE_5_HARD_ALERT_BREAKPOINTS: [f64; 2] = [2., 3.4];
    const MODE_5_HARD_ALERT_VALUES: [f64; 2] = [150., 50.];

    pub fn new_running(on_ground: bool, flight_phase: FlightPhase) -> Self {
        Self::new(Duration::ZERO, on_ground, flight_phase)
    }

    pub fn new(self_check: Duration, on_ground: bool, flight_phase: FlightPhase) -> Self {
        Self {
            pin_programs: EnhancedGroundProximityWarningComputerPinProgramming::default(),
            remaining_startup: self_check,

            reposition_mode_confirm_node: ConfirmationNode::new_falling(Duration::from_secs(3)),

            on_ground,
            flight_phase,

            chosen_vertical_speed_ft_min: 0.,
            chosen_altitude_ft: 0.,
            ra_ft: 0.,

            ground_to_air_confirm_node: ConfirmationNode::new_rising(Duration::from_secs(10)),
            takeoff_to_approach_condition_integrator: 0.,

            gpws_sys_fault: false,
            terr_sys_fault: false,
            gs_fault: false,
            vs_fault: false,
            altitude_fault: false,

            gpws_inhibit_discrete_conf_node: ConfirmationNode::new_rising(Duration::from_secs(5)),
            audio_inhibit_discrete_conf_node: ConfirmationNode::new_rising(Duration::from_secs(60)),

            mode_1_sinkrate_conf_node_1: ConfirmationNode::new_rising(Duration::from_millis(800)),
            mode_1_sinkrate_conf_node_2: ConfirmationNode::new_falling(Duration::from_millis(200)),
            mode_1_pull_up_conf_node_1: ConfirmationNode::new_rising(Duration::from_millis(1600)),
            mode_1_pull_up_conf_node_2: ConfirmationNode::new_falling(Duration::from_millis(200)),
            mode_1_sinkrate_time_to_impact_min: 0.,
            mode_1_sinkrate_emitted_for_current_time_to_impact: false,

            mode_1_sinkrate_lamp_active: false,
            mode_1_sinkrate_voice_active: false,
            mode_1_pull_up_active: false,

            mode_2_takeoff_latch_node: MonostableTriggerNode::new_falling(Duration::from_secs(60)),
            mode_2_closure_rate_derivative: DerivativeNode::new(),
            mode_2_ra_rate_limiter: RateLimiter::new_symmetrical(170.), // Roughly 10 kfpm, i.e. maximum of boundary
            mode_2_closure_rate_rate_limiter: RateLimiter::new_symmetrical(2_900.), // roughly 1.5g in ft/(min*s)
            mode_2_ra_filter: LowPassFilter::new(Duration::from_secs_f64(1.)),

            mode_2_pull_up_preface_voice_emitted: false,
            mode_2_pull_up_preface_active: false,
            mode_2_pull_up_active: false,
            mode_2_terrain_active: false,

            mode_3_max_achieved_alt_ft: 0.,

            mode_3_lamp_active: false,
            mode_3_dont_sink_voice_active: false,

            mode_4_too_low_gear_voice_active: false,
            mode_4_too_low_flaps_voice_active: false,
            mode_4_too_low_terrain_voice_active: false,

            mode_5_time_to_next_aural: Duration::ZERO,
            mode_5_declutter_threshold_increase: 0.,
            mode_5_glideslope_soft_voice_active: false,
            mode_5_glideslope_hard_voice_active: false,
            mode_5_glideslope_lamp_active: false,

            number_of_aural_warning_emissions: 0,
            time_since_first_emission: Duration::ZERO,

            warning_lamp_activated: false,
            alert_lamp_activated: false,
            aural_output: AuralWarning::None,
        }
    }

    pub fn update(
        &mut self,
        context: &UpdateContext,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
        ra1: &impl RadioAltimeter,
        ra2: &impl RadioAltimeter,
        adr: &impl AirDataReferenceBus,
        ir: &impl InertialReferenceBus,
        ils: &impl InstrumentLandingSystemBus,
    ) {
        // First, check if we're still starting up and if so, simulate a wait until all self tests
        // have completed.
        if let Some(new_remaining) = self.remaining_startup.checked_sub(context.delta()) {
            self.remaining_startup = new_remaining;
        } else {
            self.remaining_startup = Duration::ZERO;
        }

        // If there's any startup time remaining, do nothing
        if self.remaining_startup > Duration::ZERO {
            return;
        }

        // Update reposition confirm node
        self.reposition_mode_confirm_node
            .update(discrete_inputs.sim_reposition_active, context.delta());

        self.update_fault_logic(context, discrete_inputs, ra1, ra2, adr, ir, ils);
        self.update_general_logic(context, adr, ir);

        // Update GPWS Basic mode logics
        self.update_mode_1_logic(context, ils);
        self.update_mode_2_logic(context, adr, discrete_inputs, ils);
        self.update_mode_3_logic(context);
        self.update_mode_4_logic();
        self.update_mode_5_logic(context, ils, ir, discrete_inputs);

        self.compute_lamp_output(discrete_inputs);
        self.compute_aural_output(context, discrete_inputs);
    }

    fn update_general_logic(
        &mut self,
        context: &UpdateContext,
        adr: &impl AirDataReferenceBus,
        ir: &impl InertialReferenceBus,
    ) {
        // General mode logics
        let ground_to_air_ra_speed_condition =
            self.ra_ft >= 25. && adr.computed_airspeed().value() >= Velocity::new::<knot>(90.);
        self.ground_to_air_confirm_node
            .update(ground_to_air_ra_speed_condition, context.delta());
        let ground_to_air_pitch_condition =
            ir.pitch_angle().value_or_default() >= Angle::new::<degree>(5.);
        let air_to_ground_condition =
            self.ra_ft < 25. && adr.computed_airspeed().value() > Velocity::new::<knot>(60.);

        // If the reposition signal is active, skip the normal mode logic, and use reposition override logic.
        if self.reposition_mode_confirm_node.get_output() {
            self.on_ground = !ground_to_air_ra_speed_condition;
            self.flight_phase = if self.ra_ft >= 245. {
                FlightPhase::Approach
            } else {
                FlightPhase::Takeoff
            };

            return;
        }

        // On ground state machine logic
        if self.on_ground & ground_to_air_ra_speed_condition
            && (ground_to_air_pitch_condition || self.ground_to_air_confirm_node.get_output())
        {
            self.on_ground = false;
        } else if !self.on_ground && air_to_ground_condition {
            self.on_ground = true;
        }

        // Takeoff/Approach mode state machine logic
        // TODO add no mode 4B warning condition
        let approach_to_takeoff_condition = self.ra_ft < 245. && true;

        if self.flight_phase == FlightPhase::Takeoff && !self.on_ground {
            self.takeoff_to_approach_condition_integrator +=
                self.chosen_altitude_ft.max(0.).min(700.) * context.delta().as_secs_f64();
        } else {
            self.takeoff_to_approach_condition_integrator = 0.;
        }

        // TODO Implement second condition, and change integrator to use alt above field, doesn't make sense as is
        let takeoff_to_approach_condition = (!self.pin_programs.audio_declutter_disable
            && self.takeoff_to_approach_condition_integrator > 84_700.)
            || false;

        if self.flight_phase == FlightPhase::Takeoff && takeoff_to_approach_condition {
            self.flight_phase = FlightPhase::Approach;
        } else if self.flight_phase == FlightPhase::Approach && approach_to_takeoff_condition {
            self.flight_phase = FlightPhase::Takeoff;
        }
    }

    fn update_fault_logic(
        &mut self,
        context: &UpdateContext,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
        ra1: &impl RadioAltimeter,
        ra2: &impl RadioAltimeter,
        adr: &impl AirDataReferenceBus,
        ir: &impl InertialReferenceBus,
        ils: &impl InstrumentLandingSystemBus,
    ) {
        // Input selection and monitoring logic

        // RA computation (TODO implement reasonableness check and maybe filtering)
        let ra_fault =
            ra1.radio_altitude().is_failure_warning() && ra2.radio_altitude().is_failure_warning();
        if !ra1.radio_altitude().is_failure_warning() && !ra2.radio_altitude().is_failure_warning()
        {
            let ra1_ft = ra1.radio_altitude().value().get::<foot>();
            let ra2_ft = ra2.radio_altitude().value().get::<foot>();

            self.ra_ft = if ra1_ft < 2500. || ra2_ft < 2500. && (ra1_ft - ra2_ft).abs() < 500. {
                ra1_ft
            } else {
                // Consistency check failed. Use the greater of the two values
                ra1_ft.max(ra2_ft)
            }
        } else if !ra1.radio_altitude().is_failure_warning() {
            self.ra_ft = ra1.radio_altitude().value().get::<foot>();
        } else if !ra2.radio_altitude().is_failure_warning() {
            self.ra_ft = ra2.radio_altitude().value().get::<foot>();
        } else {
            // Both RAs are faulty
            self.ra_ft = 0.;
        }

        // V/S Selection: First, choose IR Baro-Inertial Vertical speed, if valid. Otherwise, choose internally computed Baro-Inertial Vertical speed, if valid (not implemented)
        // Finally, choose the ADR barometric Vertical speed.
        self.vs_fault = false;
        self.chosen_vertical_speed_ft_min =
            if let Some(vs) = ir.inertial_vertical_speed().normal_value() {
                vs
            } else if let Some(vs) = adr.vertical_speed().normal_value() {
                vs
            } else {
                self.vs_fault = true;
                adr.vertical_speed().value_or_default()
            }
            .get::<foot_per_minute>();

        // Same deal as above here
        self.altitude_fault = false;
        self.chosen_altitude_ft = if let Some(alt) = ir.inertial_altitude().normal_value() {
            alt
        } else if let Some(alt) = adr.standard_altitude().normal_value() {
            alt
        } else {
            self.altitude_fault = true;
            adr.standard_altitude().value_or_default()
        }
        .get::<foot>();

        let cas_fault = adr.computed_airspeed().is_failure_warning();

        self.gs_fault = ils.glideslope_deviation().is_failure_warning();

        self.audio_inhibit_discrete_conf_node
            .update(discrete_inputs.audio_inhibit, context.delta());
        self.gpws_inhibit_discrete_conf_node
            .update(discrete_inputs.gpws_inhibit, context.delta());

        let total_failure_due_to_peripherals = ra_fault || cas_fault;

        self.gpws_sys_fault = self.audio_inhibit_discrete_conf_node.get_output()
            || self.gpws_inhibit_discrete_conf_node.get_output()
            || total_failure_due_to_peripherals;
        // TODO Implement TERR sys
        self.terr_sys_fault = false;
    }

    fn update_mode_1_logic(
        &mut self,
        context: &UpdateContext,
        ils: &impl InstrumentLandingSystemBus,
    ) {
        // TODO implement steep approach logic
        // If the audio declutter is enabled, bias vertical speed when above the beam to remove unnecessary warnings
        // when repositioning to the beam.
        let biased_vertical_speed = if self.pin_programs.audio_declutter_disable {
            self.chosen_vertical_speed_ft_min
        } else {
            self.chosen_vertical_speed_ft_min
                + 300.
                    * (self.ra_ft / 100.).clamp(0., 1.)
                    * (ils.glideslope_deviation().value().get::<ratio>() / 0.175).clamp(0., 1.)
        };

        let mode_1_alert_boundary_met = interpolation(
            &Self::MODE_1_ALERT_AREA_BREAKPOINTS,
            &Self::MODE_1_ALERT_AREA_VALUES,
            biased_vertical_speed,
        ) >= self.ra_ft
            && self.ra_ft > 10.
            && self.ra_ft < 2450.
            && biased_vertical_speed < -964.;

        let mode_1_warning_boundary_met = interpolation(
            &Self::MODE_1_WARNING_AREA_BREAKPOINTS,
            &Self::MODE_1_WARNING_AREA_VALUES,
            self.chosen_vertical_speed_ft_min,
        ) >= self.ra_ft
            && self.ra_ft > 10.
            && self.ra_ft < 2450.
            && self.chosen_vertical_speed_ft_min < -1482.;

        self.mode_1_sinkrate_lamp_active = self.mode_1_sinkrate_conf_node_2.update(
            self.mode_1_sinkrate_conf_node_1
                .update(mode_1_alert_boundary_met, context.delta()),
            context.delta(),
        );

        self.mode_1_pull_up_active = self.mode_1_pull_up_conf_node_2.update(
            self.mode_1_pull_up_conf_node_1
                .update(mode_1_warning_boundary_met, context.delta()),
            context.delta(),
        );

        // Perform the time to impact ratcheting logic for the sinkrate aural warning (only used with audio declutter)
        let current_time_to_impact_min = self.ra_ft / -self.chosen_vertical_speed_ft_min;

        let time_to_impact_worsened_by_20_percent =
            current_time_to_impact_min < self.mode_1_sinkrate_time_to_impact_min * 0.8;

        // Store the time to impact at last emission
        if (self.mode_1_sinkrate_time_to_impact_min == 0. || time_to_impact_worsened_by_20_percent)
            && self.mode_1_sinkrate_lamp_active
        {
            self.mode_1_sinkrate_time_to_impact_min = current_time_to_impact_min;
        } else if !self.mode_1_sinkrate_lamp_active {
            self.mode_1_sinkrate_time_to_impact_min = 0.;
        }

        let sinkrate_voice_emitted_twice = self.number_of_aural_warning_emissions >= 2
            && self.aural_output == AuralWarning::SinkRate;

        // If the voice has been emitted twice for the current time to impact, set the flag.
        // Else if the time to impact has worsened by 20% or the lamp is no longer active, reset the flag.
        if !self.mode_1_sinkrate_emitted_for_current_time_to_impact
            && sinkrate_voice_emitted_twice
            && !time_to_impact_worsened_by_20_percent
        {
            self.mode_1_sinkrate_emitted_for_current_time_to_impact = true;
        } else if (self.mode_1_sinkrate_emitted_for_current_time_to_impact
            && time_to_impact_worsened_by_20_percent)
            || !self.mode_1_sinkrate_lamp_active
        {
            self.mode_1_sinkrate_emitted_for_current_time_to_impact = false;
        }

        self.mode_1_sinkrate_voice_active = self.mode_1_sinkrate_lamp_active
            && !self.mode_1_pull_up_active
            && (self.pin_programs.audio_declutter_disable
                || !self.mode_1_sinkrate_emitted_for_current_time_to_impact);
    }

    fn update_mode_2_logic(
        &mut self,
        context: &UpdateContext,
        adr: &impl AirDataReferenceBus,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
        ils: &impl InstrumentLandingSystemBus,
    ) {
        self.mode_2_takeoff_latch_node
            .update(self.on_ground, context.delta());

        // Calculate and filter closure rate. We have it even worse than in IRL, because the sim in it's
        // infinite wisdom decides to potentially update the RA at a potentially low rate
        // (depening on RA, down to less than 1Hz)
        let ra_ratelim = self
            .mode_2_ra_rate_limiter
            .update(context.delta(), self.ra_ft);

        self.mode_2_closure_rate_derivative
            .update(ra_ratelim, context.delta());
        let closure_rate_ft_per_min_raw = self.mode_2_closure_rate_derivative.output() * -60.; // ft/s to ft/min

        let filtered_closure_rate_ft = self.mode_2_ra_filter.update(
            context.delta(),
            self.mode_2_closure_rate_rate_limiter
                .update(context.delta(), closure_rate_ft_per_min_raw),
        );

        // Compute boundaries

        // TODO implement TCF and TERR function active conditions
        let mode_2_b_active = self.mode_2_takeoff_latch_node.output()
            || discrete_inputs.landing_flaps
            || (ils.glideslope_deviation().is_normal_operation()
                && ils.localizer_deviation().is_normal_operation()
                && ils.glideslope_deviation().value().abs() < Ratio::new::<ratio>(0.175)
                && ils.localizer_deviation().value().abs() < Ratio::new::<ratio>(0.155));

        let mode_2_upper_boundary_ft = if mode_2_b_active {
            789.
        } else {
            // TODO limit mode 2A upper boundary when TERR function active
            (1650. + 8.9 * (adr.computed_airspeed().value_or_default().get::<knot>() - 220.))
                .clamp(1650., 2450.)
        };
        let mode_2_lower_boundary_ft = if mode_2_b_active && discrete_inputs.landing_flaps {
            interpolation(
                &Self::MODE_2_B_CUTOFF_AREA_BREAKPOINTS,
                &Self::MODE_2_B_CUTOFF_AREA_VALUES,
                self.chosen_vertical_speed_ft_min,
            )
        } else {
            30.
        };

        let mode_2_boundary_met = interpolation(
            &Self::MODE_2_ALERT_AREA_BREAKPOINTS,
            &Self::MODE_2_ALERT_AREA_VALUES,
            filtered_closure_rate_ft,
        ) >= self.ra_ft
            && filtered_closure_rate_ft > 2038.
            && self.ra_ft > mode_2_lower_boundary_ft
            && self.ra_ft < mode_2_upper_boundary_ft;

        // Compute Warning logics
        let aural_terrain_only =
            discrete_inputs.landing_flaps && discrete_inputs.landing_gear_downlocked;

        if mode_2_boundary_met && !self.mode_2_pull_up_preface_voice_emitted && !aural_terrain_only
        {
            self.mode_2_pull_up_preface_voice_emitted = self.number_of_aural_warning_emissions >= 2
                && self.aural_output == AuralWarning::Terrain;
        } else if !mode_2_boundary_met || aural_terrain_only {
            self.mode_2_pull_up_preface_voice_emitted = false;
        }

        // TODO Implement mode 2A altitude gain condition

        self.mode_2_pull_up_preface_active = !aural_terrain_only
            && mode_2_boundary_met
            && !self.mode_2_pull_up_preface_voice_emitted;
        self.mode_2_pull_up_active =
            !aural_terrain_only && mode_2_boundary_met && self.mode_2_pull_up_preface_voice_emitted;
        self.mode_2_terrain_active = aural_terrain_only && mode_2_boundary_met;

        //println!(
        //    "Mode 2: ra: {:.1} ft, ra_lim: {:.1} ft, closure rate: {:.1} ({:.1} raw) ft/min, lower boundary: {:.1} ft, upper boundary: {:.1} ft,
        //    boundary met: {}, preface emitted: {}, preface active: {}, pull up active: {}, terrain active: {}",
        //    self.ra_ft,
        //    ra_ratelim,
        //    filtered_closure_rate_ft,
        //    closure_rate_ft_per_min_raw,
        //    mode_2_lower_boundary_ft,
        //    mode_2_upper_boundary_ft,
        //    mode_2_boundary_met,
        //    self.mode_2_pull_up_preface_voice_emitted,
        //    self.mode_2_pull_up_preface_active,
        //    self.mode_2_pull_up_active,
        //    self.mode_2_terrain_active,
        //);
    }

    fn update_mode_3_logic(&mut self, context: &UpdateContext) {
        let mode_3_enabled = self.flight_phase == FlightPhase::Takeoff
            && self.ra_ft < 1500.
            && self.chosen_vertical_speed_ft_min < 0.;

        let altitude_loss_ft = self.mode_3_max_achieved_alt_ft - self.chosen_altitude_ft;

        // TODO Implement bias
        let mode_3_boundary_met = interpolation(
            &Self::MODE_3_ALERT_AREA_BREAKPOINTS,
            &Self::MODE_3_ALERT_AREA_VALUES,
            altitude_loss_ft,
        ) < self.ra_ft
            && altitude_loss_ft > 8.
            && self.ra_ft > 30.;
        self.mode_3_lamp_active = mode_3_boundary_met;
    }

    fn update_mode_4_logic(&mut self) {}

    fn update_mode_5_logic(
        &mut self,
        context: &UpdateContext,
        ils: &impl InstrumentLandingSystemBus,
        ir: &impl InertialReferenceBus,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
    ) {
        // 0.0875 is 1 dot
        let loc_deviation_dots = ils.localizer_deviation().value().get::<ratio>() / 0.0775;
        let gs_deviation_dots_fly_up = -ils.glideslope_deviation().value().get::<ratio>() / 0.0875;

        let fls_selected = false; // TODO implement
        let mix_loc_fls_selected = false; // TODO implement
        let heading_difference = (ir.magnetic_track().value().get::<degree>()
            - ils.runway_heading().value().get::<degree>()
            + 540.)
            % 360.
            - 180.;
        let mode_5_active = !fls_selected
            && !mix_loc_fls_selected
            && ils.glideslope_deviation().is_normal_operation()
            && !discrete_inputs.glideslop_inhibit
            && (discrete_inputs.landing_flaps || self.flight_phase == FlightPhase::Approach)
            && (discrete_inputs.landing_gear_downlocked || false) // TODO Implement envelope modulation override
            && (heading_difference.abs() < 50. || !ir.magnetic_track().is_normal_operation())
            && (loc_deviation_dots.abs() < 2. || self.ra_ft < 500.);

        let mode_5_hard_alert_boundary_met = interpolation(
            &Self::MODE_5_HARD_ALERT_BREAKPOINTS,
            &Self::MODE_5_HARD_ALERT_VALUES,
            gs_deviation_dots_fly_up,
        ) < self.ra_ft
            && gs_deviation_dots_fly_up > 2.0
            && self.ra_ft < 300.
            && self.ra_ft > 50.
            && mode_5_active;

        let mode_5_soft_alert_upper_boundary_ft = interpolation(
            &Self::MODE_5_SOFT_ALERT_UPPER_BOUNDARY_BREAKPOINTS,
            &Self::MODE_5_SOFT_ALERT_UPPER_BOUNDARY_VALUES,
            self.chosen_vertical_speed_ft_min,
        );
        let mode_5_soft_alert_light_boundary_met = interpolation(
            &Self::MODE_5_SOFT_ALERT_BREAKPOINTS,
            &Self::MODE_5_SOFT_ALERT_VALUES,
            gs_deviation_dots_fly_up,
        ) < self.ra_ft
            && gs_deviation_dots_fly_up > 1.3
            && self.ra_ft < mode_5_soft_alert_upper_boundary_ft
            && self.ra_ft > 50.
            && mode_5_active;

        let soft_alert_aural_boundary_biased =
            gs_deviation_dots_fly_up / (1. + self.mode_5_declutter_threshold_increase);
        let mode_5_soft_alert_aural_boundary_met = interpolation(
            &Self::MODE_5_SOFT_ALERT_BREAKPOINTS,
            &Self::MODE_5_SOFT_ALERT_VALUES,
            soft_alert_aural_boundary_biased,
        ) < self.ra_ft
            && soft_alert_aural_boundary_biased > 1.3
            && self.ra_ft < mode_5_soft_alert_upper_boundary_ft
            && self.ra_ft > 50.
            && mode_5_active;

        self.mode_5_glideslope_lamp_active = mode_5_active
            && (mode_5_soft_alert_light_boundary_met || mode_5_hard_alert_boundary_met);

        if self.pin_programs.audio_declutter_disable {
            // Without audio declutter, the aural warnings are always active when in the alert area,
            // with a pause between emissions based on RA and G/S deviation
            self.mode_5_glideslope_soft_voice_active = mode_5_soft_alert_aural_boundary_met
                && !mode_5_hard_alert_boundary_met
                && self.mode_5_time_to_next_aural == Duration::ZERO;
            self.mode_5_glideslope_hard_voice_active =
                mode_5_hard_alert_boundary_met && self.mode_5_time_to_next_aural == Duration::ZERO;

            let mode_5_aural_pause =
                Duration::from_secs_f64(self.ra_ft / gs_deviation_dots_fly_up.abs() * 0.0067);
            if !(mode_5_hard_alert_boundary_met || mode_5_soft_alert_aural_boundary_met) {
                self.mode_5_time_to_next_aural = Duration::ZERO;
            } else if self.mode_5_time_to_next_aural == Duration::ZERO
                && (self.aural_output == AuralWarning::GlideslopeHard
                    || self.aural_output == AuralWarning::GlideslopeSoft)
                && self.number_of_aural_warning_emissions > 0
            {
                self.mode_5_time_to_next_aural = mode_5_aural_pause;
            } else {
                self.mode_5_time_to_next_aural = self
                    .mode_5_time_to_next_aural
                    .checked_sub(context.delta())
                    .unwrap_or(Duration::ZERO);
            }
        } else {
            // With audio declutter, the hard aural warning is always active in the hard alert area, with an emission pause of around 3s.
            // The soft aural warning is only active once when the threshold is met, then a 20% increase in G/S deviation is required to
            // emit a new alert.
            self.mode_5_glideslope_soft_voice_active =
                mode_5_soft_alert_aural_boundary_met && !mode_5_hard_alert_boundary_met;
            self.mode_5_glideslope_hard_voice_active =
                mode_5_hard_alert_boundary_met && self.mode_5_time_to_next_aural == Duration::ZERO;

            if !mode_5_soft_alert_light_boundary_met {
                self.mode_5_declutter_threshold_increase = 0.;
            } else if self.mode_5_glideslope_soft_voice_active
                && self.aural_output == AuralWarning::GlideslopeSoft
                && self.number_of_aural_warning_emissions > 0
            {
                self.mode_5_declutter_threshold_increase += 0.2;
            }

            if !mode_5_hard_alert_boundary_met {
                self.mode_5_time_to_next_aural = Duration::ZERO;
            } else if self.mode_5_time_to_next_aural == Duration::ZERO
                && self.aural_output == AuralWarning::GlideslopeHard
                && self.number_of_aural_warning_emissions > 0
            {
                self.mode_5_time_to_next_aural = Duration::from_secs(3);
            } else {
                self.mode_5_time_to_next_aural = self
                    .mode_5_time_to_next_aural
                    .checked_sub(context.delta())
                    .unwrap_or(Duration::ZERO);
            }

            //println!(
            //    "Mode 5: ra: {:.1} ft, gs dev: {:.2} dots, mode 5 active: {}, soft light met: {}, soft aural met: {}, hard met: {},
            //    soft_upper_bound: {:.1}ft, soft voice active: {}, hard voice active: {}, declutter increase: {:.1}, time to next aural: {:.1} s",
            //    self.ra_ft,
            //    gs_deviation_dots_fly_up,
            //    mode_5_active,
            //    mode_5_soft_alert_light_boundary_met,
            //    mode_5_soft_alert_aural_boundary_met,
            //    mode_5_hard_alert_boundary_met,
            //    mode_5_soft_alert_upper_boundary_ft,
            //    self.mode_5_glideslope_soft_voice_active,
            //    self.mode_5_glideslope_hard_voice_active,
            //    self.mode_5_declutter_threshold_increase,
            //    self.mode_5_time_to_next_aural.as_secs_f64(),
            //);
        }
    }

    fn compute_lamp_output(
        &mut self,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
    ) {
        if self.pin_programs.alternate_lamp_format {
            // TODO Complete rest of the modes.
            self.warning_lamp_activated = (self.mode_1_pull_up_active
                || self.mode_2_pull_up_active)
                && !discrete_inputs.gpws_inhibit;
            self.alert_lamp_activated = (self.mode_1_sinkrate_lamp_active
                || self.mode_2_pull_up_preface_active
                || self.mode_2_terrain_active
                || self.mode_5_glideslope_lamp_active)
                && !discrete_inputs.gpws_inhibit;
        } else {
            self.warning_lamp_activated = (self.mode_1_sinkrate_lamp_active
                || self.mode_1_pull_up_active
                || self.mode_2_pull_up_active
                || self.mode_2_pull_up_preface_active
                || self.mode_2_terrain_active)
                && !discrete_inputs.gpws_inhibit;
            self.alert_lamp_activated =
                self.mode_5_glideslope_lamp_active && !discrete_inputs.gpws_inhibit;
        }
    }

    fn compute_aural_output(
        &mut self,
        context: &UpdateContext,
        discrete_inputs: &TerrainAwarenessWarningSystemDiscreteInputs,
    ) {
        let prev_aural_output = self.aural_output;

        let basic_gpws_inhibit = discrete_inputs.gpws_inhibit || discrete_inputs.audio_inhibit;

        if self.mode_1_pull_up_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::PullUp;
        } else if self.mode_2_pull_up_preface_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::Terrain;
        } else if self.mode_2_pull_up_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::PullUp;
        } else if self.mode_2_terrain_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::Terrain;
        } else if self.mode_4_too_low_terrain_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::TooLowTerrain;
        } else if self.mode_4_too_low_gear_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::TooLowGear;
        } else if self.mode_4_too_low_flaps_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::TooLowFlaps;
        } else if self.mode_1_sinkrate_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::SinkRate;
        } else if self.mode_3_dont_sink_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::DontSink;
        } else if self.mode_5_glideslope_soft_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::GlideslopeSoft;
        } else if self.mode_5_glideslope_hard_voice_active && !basic_gpws_inhibit {
            self.aural_output = AuralWarning::GlideslopeHard;
        } else {
            self.aural_output = AuralWarning::None;
        }

        // Also compute the number of times the current active aural warning has been emitted
        // This is used in different warning logics (i.e. Mode 1 sink rate warning)
        if prev_aural_output != self.aural_output || self.aural_output == AuralWarning::None {
            self.number_of_aural_warning_emissions = 0;
            self.time_since_first_emission = Duration::ZERO;
        } else if self.aural_output != AuralWarning::None {
            self.time_since_first_emission += context.delta();
            self.number_of_aural_warning_emissions = (self.time_since_first_emission.as_secs_f64()
                / self.aural_output.get_duration().as_secs_f64())
            .floor() as u32;
        }
    }

    pub fn get_aural_output(&self) -> AuralWarning {
        self.aural_output
    }

    pub fn get_on_ground(&self) -> bool {
        self.on_ground
    }

    pub fn get_flight_phase(&self) -> FlightPhase {
        self.flight_phase
    }

    pub fn set_outputs(
        &self,
        discrete_outputs: &mut TerrainAwarenessWarningSystemDiscreteOutputs,
        bus_outputs: &mut TerrainAwarenessWarningSystemBusOutputs,
    ) {
        discrete_outputs.alert_lamp = self.alert_lamp_activated;
        discrete_outputs.warning_lamp = self.warning_lamp_activated;
        discrete_outputs.audio_on = self.aural_output != AuralWarning::None;
        discrete_outputs.terrain_obstacle_caution = false;
        discrete_outputs.terrain_obstacle_warning = false;
        discrete_outputs.gpws_inop = self.gpws_sys_fault || self.remaining_startup > Duration::ZERO;
        discrete_outputs.terrain_inop =
            self.terr_sys_fault || self.remaining_startup > Duration::ZERO;
        discrete_outputs.terrain_not_available = false;
        discrete_outputs.raas_inop = false;
        discrete_outputs.capt_terrain_display_active = false;
        discrete_outputs.fo_terrain_display_active = false;
        discrete_outputs.tcas_inhibit = false;
    }
}
