use uom::si::{
    electric_potential::volt,
    f64::{
        Angle, AngularAcceleration, AngularVelocity, ElectricPotential, Frequency, Length,
        Pressure, Ratio, ThermodynamicTemperature, Velocity,
    },
    length::foot,
    velocity::{foot_per_minute, knot},
};

use crate::{
    electrical::{test::TestElectricitySource, ElectricalBus, Electricity},
    shared::{
        arinc429::{Arinc429Word, SignStatus},
        LgciuGearExtension, MachNumber, PotentialOrigin, PowerConsumptionReport,
    },
    simulation::{
        test::{ReadByName, SimulationTestBed, TestBed, WriteByName},
        Aircraft, Read, SimulatorReader, StartState,
    },
};

use super::*;

struct TestLgciu {
    extended: bool,
}
impl TestLgciu {
    fn new(extended: bool) -> Self {
        Self { extended }
    }

    fn set_gear_extended(&mut self, extended: bool) {
        self.extended = extended;
    }
}
impl LgciuGearExtension for TestLgciu {
    fn all_down_and_locked(&self) -> bool {
        self.extended
    }
    fn all_up_and_locked(&self) -> bool {
        !self.extended
    }
    fn main_down_and_locked(&self) -> bool {
        self.extended
    }
    fn main_up_and_locked(&self) -> bool {
        !self.extended
    }
    fn nose_down_and_locked(&self) -> bool {
        self.extended
    }
    fn nose_up_and_locked(&self) -> bool {
        !self.extended
    }
    fn left_down_and_locked(&self) -> bool {
        self.extended
    }
}

struct TestRa {
    radio_altitude: Length,
    failed: bool,

    altitude_id: VariableIdentifier,
    terr_height_id: VariableIdentifier,
}
impl RadioAltimeter for TestRa {
    fn radio_altitude(&self) -> Arinc429Word<Length> {
        if self.failed {
            Arinc429Word::new(Length::default(), SignStatus::FailureWarning)
        } else if self.radio_altitude < Length::new::<foot>(-20.) {
            Arinc429Word::new(Length::new::<foot>(-20.), SignStatus::NoComputedData)
        } else if self.radio_altitude > Length::new::<foot>(8192.) {
            Arinc429Word::new(Length::new::<foot>(8192.), SignStatus::NoComputedData)
        } else {
            Arinc429Word::new(self.radio_altitude, SignStatus::NormalOperation)
        }
    }
}
impl TestRa {
    const ALTITUDE_KEY: &str = "TEST_RA_RADIO_ALTITUDE";
    const TERRAIN_HEIGHT_KEY: &str = "TEST_RA_TERRAIN_HEIGHT";

    fn new(context: &mut InitContext, radio_altitude: Length) -> Self {
        Self {
            radio_altitude,
            failed: false,

            altitude_id: context.get_identifier(Self::ALTITUDE_KEY.to_owned()),
            terr_height_id: context.get_identifier(Self::TERRAIN_HEIGHT_KEY.to_owned()),
        }
    }

    fn set_failed(&mut self, failed: bool) {
        self.failed = failed;
    }
}
impl SimulationElement for TestRa {
    fn read(&mut self, reader: &mut SimulatorReader) {
        self.radio_altitude = Read::<Length>::read(reader, &self.altitude_id)
            - Read::<Length>::read(reader, &self.terr_height_id);
    }
}

struct TestAdiru {
    computed_airspeed: Velocity,
    altitude: Length,
    vertical_speed: Velocity,
    pitch: Angle,

    altitude_id: VariableIdentifier,
    vertical_speed_id: VariableIdentifier,
    cas_id: VariableIdentifier,
}
impl TestAdiru {
    const VERTICAL_SPEED_KEY: &str = "VERTICAL_SPEED";
    const CAS_KEY: &str = "COMPUTED_AIRSPEED";

    fn new(context: &mut InitContext) -> Self {
        Self {
            computed_airspeed: Velocity::default(),
            altitude: Length::default(),
            vertical_speed: Velocity::default(),
            pitch: Angle::default(),

            altitude_id: context.get_identifier(TestRa::ALTITUDE_KEY.to_owned()),
            vertical_speed_id: context.get_identifier(Self::VERTICAL_SPEED_KEY.to_owned()),
            cas_id: context.get_identifier(Self::CAS_KEY.to_owned()),
        }
    }
}
impl AirDataReferenceBus for TestAdiru {
    fn standard_altitude(&self) -> Arinc429Word<Length> {
        Arinc429Word::new(self.altitude, SignStatus::NormalOperation)
    }
    fn baro_corrected_altitude_1(&self) -> Arinc429Word<Length> {
        Arinc429Word::new(self.altitude, SignStatus::NormalOperation)
    }
    fn mach(&self) -> Arinc429Word<MachNumber> {
        Arinc429Word::new(MachNumber::default(), SignStatus::NormalOperation)
    }
    fn computed_airspeed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(self.computed_airspeed, SignStatus::NormalOperation)
    }
    fn max_allowable_airspeed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(Velocity::default(), SignStatus::NormalOperation)
    }
    fn true_airspeed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(self.computed_airspeed, SignStatus::NormalOperation)
    }
    fn total_air_temperature(&self) -> Arinc429Word<ThermodynamicTemperature> {
        Arinc429Word::new(
            ThermodynamicTemperature::default(),
            SignStatus::NormalOperation,
        )
    }
    fn vertical_speed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(self.vertical_speed, SignStatus::NormalOperation)
    }
    fn static_air_temperature(&self) -> Arinc429Word<ThermodynamicTemperature> {
        Arinc429Word::new(
            ThermodynamicTemperature::default(),
            SignStatus::NormalOperation,
        )
    }
    fn baro_corrected_altitude_2(&self) -> Arinc429Word<Length> {
        Arinc429Word::new(self.altitude, SignStatus::NormalOperation)
    }
    fn baro_correction_1(&self) -> Arinc429Word<Pressure> {
        Arinc429Word::new(Pressure::default(), SignStatus::NormalOperation)
    }
    fn baro_correction_2(&self) -> Arinc429Word<Pressure> {
        Arinc429Word::new(Pressure::default(), SignStatus::NormalOperation)
    }
    fn corrected_angle_of_attack(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
}
impl InertialReferenceBus for TestAdiru {
    /// Label 052
    fn pitch_angular_acc(&self) -> Arinc429Word<AngularAcceleration> {
        Arinc429Word::new(AngularAcceleration::default(), SignStatus::NormalOperation)
    }
    /// Label 053
    fn roll_angular_acc(&self) -> Arinc429Word<AngularAcceleration> {
        Arinc429Word::new(AngularAcceleration::default(), SignStatus::NormalOperation)
    }
    /// Label 053
    fn yaw_angular_acc(&self) -> Arinc429Word<AngularAcceleration> {
        Arinc429Word::new(AngularAcceleration::default(), SignStatus::NormalOperation)
    }
    /// Label 310
    fn ppos_latitude(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 311
    fn ppos_longitude(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 312
    fn ground_speed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(Velocity::default(), SignStatus::NormalOperation)
    }
    /// Label 313
    fn true_heading(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 314
    fn true_track(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 315
    fn wind_speed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(Velocity::default(), SignStatus::NormalOperation)
    }
    /// Label 316
    fn wind_dir_true(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 317
    fn magnetic_track(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 320
    fn magnetic_heading(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 321
    fn drift_angle(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 322
    fn flight_path_angle(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 323
    fn flight_path_accel(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(Ratio::default(), SignStatus::NormalOperation)
    }
    /// Label 324
    fn pitch_angle(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(self.pitch, SignStatus::NormalOperation)
    }
    /// Label 325
    fn roll_angle(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(Angle::default(), SignStatus::NormalOperation)
    }
    /// Label 326
    fn body_pitch_rate(&self) -> Arinc429Word<AngularVelocity> {
        Arinc429Word::new(AngularVelocity::default(), SignStatus::NormalOperation)
    }
    /// Label 327
    fn body_roll_rate(&self) -> Arinc429Word<AngularVelocity> {
        Arinc429Word::new(AngularVelocity::default(), SignStatus::NormalOperation)
    }
    /// Label 330
    fn body_yaw_rate(&self) -> Arinc429Word<AngularVelocity> {
        Arinc429Word::new(AngularVelocity::default(), SignStatus::NormalOperation)
    }
    /// Label 331
    fn body_long_acc(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(Ratio::default(), SignStatus::NormalOperation)
    }
    /// Label 332
    fn body_lat_acc(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(Ratio::default(), SignStatus::NormalOperation)
    }
    /// Label 333
    fn body_normal_acc(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(Ratio::default(), SignStatus::NormalOperation)
    }
    /// Label 361
    fn inertial_altitude(&self) -> Arinc429Word<Length> {
        Arinc429Word::new(self.altitude, SignStatus::NormalOperation)
    }
    /// Label 365
    fn inertial_vertical_speed(&self) -> Arinc429Word<Velocity> {
        Arinc429Word::new(self.vertical_speed, SignStatus::NormalOperation)
    }

    /// Label 270
    fn discrete_word_1(&self) -> Arinc429Word<u32> {
        Arinc429Word::new(0u32, SignStatus::NormalOperation)
    }
    /// Label 275
    fn discrete_word_2(&self) -> Arinc429Word<u32> {
        Arinc429Word::new(0u32, SignStatus::NormalOperation)
    }
    /// Label 276
    fn discrete_word_3(&self) -> Arinc429Word<u32> {
        Arinc429Word::new(0u32, SignStatus::NormalOperation)
    }
}
impl SimulationElement for TestAdiru {
    fn read(&mut self, reader: &mut SimulatorReader) {
        self.altitude = reader.read(&self.altitude_id);
        self.vertical_speed = reader.read(&self.vertical_speed_id);
        self.computed_airspeed = reader.read(&self.cas_id);
    }
}

struct TestIls {
    has_glideslope: bool,
    glideslope_deviation: Ratio,
    failed: bool,
}
impl TestIls {
    fn new() -> Self {
        Self {
            has_glideslope: false,
            glideslope_deviation: Ratio::default(),
            failed: false,
        }
    }

    fn set_failed(&mut self, failed: bool) {
        self.failed = failed;
    }
}
impl InstrumentLandingSystemBus for TestIls {
    fn glideslope_deviation(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(
            self.glideslope_deviation,
            if self.failed {
                SignStatus::FailureWarning
            } else if self.has_glideslope {
                SignStatus::NormalOperation
            } else {
                SignStatus::NoComputedData
            },
        )
    }
    fn localizer_deviation(&self) -> Arinc429Word<Ratio> {
        Arinc429Word::new(
            Ratio::default(),
            if self.failed {
                SignStatus::FailureWarning
            } else {
                SignStatus::NormalOperation
            },
        )
    }
    fn runway_heading(&self) -> Arinc429Word<Angle> {
        Arinc429Word::new(
            Angle::default(),
            if self.failed {
                SignStatus::FailureWarning
            } else {
                SignStatus::NormalOperation
            },
        )
    }
    fn ils_frequency(&self) -> Arinc429Word<uom::si::f64::Frequency> {
        Arinc429Word::new(Frequency::default(), SignStatus::NormalOperation)
    }
    fn ground_station_ident_1(&self) -> Arinc429Word<u32> {
        Arinc429Word::new(0u32, SignStatus::NormalOperation)
    }
    fn ground_station_ident_2(&self) -> Arinc429Word<u32> {
        Arinc429Word::new(0u32, SignStatus::NormalOperation)
    }
}

struct TestAircraft {
    electricity_source: TestElectricitySource,
    ac_1_bus: ElectricalBus,
    lgciu: TestLgciu,
    ra: TestRa,
    adiru: TestAdiru,
    ils: TestIls,
    egpws_electrical_harness: EgpwsElectricalHarness,
    egpwc: EnhancedGroundProximityWarningComputer,
    is_ac_1_powered: bool,
    power_consumption: Power,
}
impl TestAircraft {
    fn new(context: &mut InitContext) -> Self {
        Self {
            electricity_source: TestElectricitySource::powered(
                context,
                PotentialOrigin::EngineGenerator(1),
            ),
            ac_1_bus: ElectricalBus::new(context, ElectricalBusType::AlternatingCurrent(1)),
            lgciu: TestLgciu::new(false),
            ra: TestRa::new(context, Length::new::<foot>(0.0)),
            adiru: TestAdiru::new(context),
            ils: TestIls::new(),
            egpws_electrical_harness: EgpwsElectricalHarness::new(context),
            egpwc: EnhancedGroundProximityWarningComputer::new(
                context,
                ElectricalBusType::AlternatingCurrent(1),
            ),
            is_ac_1_powered: false,
            power_consumption: Power::new::<watt>(0.),
        }
    }

    fn set_ac_1_power(&mut self, is_powered: bool) {
        self.is_ac_1_powered = is_powered;
    }
}
impl Aircraft for TestAircraft {
    fn update_before_power_distribution(
        &mut self,
        _: &UpdateContext,
        electricity: &mut Electricity,
    ) {
        self.electricity_source
            .power_with_potential(ElectricPotential::new::<volt>(115.));
        electricity.supplied_by(&self.electricity_source);

        if self.is_ac_1_powered {
            electricity.flow(&self.electricity_source, &self.ac_1_bus);
        }
    }

    fn update_after_power_distribution(&mut self, context: &UpdateContext) {
        self.egpws_electrical_harness.update(&self.lgciu);
        self.egpwc.update(
            context,
            &self.egpws_electrical_harness,
            &self.ra,
            &self.ra,
            &self.adiru,
            &self.adiru,
            &self.ils,
        );
    }
}
impl SimulationElement for TestAircraft {
    fn process_power_consumption_report<T: PowerConsumptionReport>(
        &mut self,
        _: &UpdateContext,
        report: &T,
    ) {
        self.power_consumption = report.total_consumption_of(PotentialOrigin::EngineGenerator(1));
    }

    fn accept<T: SimulationElementVisitor>(&mut self, visitor: &mut T) {
        //self.ils.accept(visitor);
        self.adiru.accept(visitor);
        self.ra.accept(visitor);
        //self.lgciu.accept(visitor);
        self.egpwc.accept(visitor);
        self.egpws_electrical_harness.accept(visitor);

        visitor.visit(self);
    }
}

struct EgpwcTestBed {
    test_bed: SimulationTestBed<TestAircraft>,
}
impl EgpwcTestBed {
    fn new() -> Self {
        let mut test_bed = Self {
            test_bed: SimulationTestBed::new_with_start_state(
                StartState::Cruise,
                TestAircraft::new,
            ),
        };
        test_bed = test_bed.on_ground().powered();

        test_bed
    }

    fn and(self) -> Self {
        self
    }

    fn no_power(mut self) -> Self {
        self.command(|a| a.set_ac_1_power(false));
        self
    }

    fn powered(mut self) -> Self {
        self.command(|a| a.set_ac_1_power(true));
        self
    }

    fn on_ground(mut self) -> Self {
        let terr_height = ReadByName::<EgpwcTestBed, Length>::read_by_name(
            &mut self,
            EnhancedGroundProximityWarningComputer::AURAL_OUTPUT_KEY,
        );
        self.altitude_of(terr_height).gear_position(true)
    }

    fn altitude_of(mut self, height: Length) -> Self {
        self.write_by_name(TestRa::ALTITUDE_KEY, height);
        self
    }

    fn terrain_height_of(mut self, height: Length) -> Self {
        self.write_by_name(TestRa::TERRAIN_HEIGHT_KEY, height);
        self
    }

    fn vertical_speed_of(mut self, vs: Velocity) -> Self {
        self.write_by_name(TestAdiru::VERTICAL_SPEED_KEY, vs);
        self
    }

    fn cas_of(mut self, vs: Velocity) -> Self {
        self.write_by_name(TestAdiru::CAS_KEY, vs);
        self
    }

    fn gear_position(mut self, extended: bool) -> Self {
        self.command(|a| a.lgciu.set_gear_extended(extended));
        self
    }

    fn flaps_mode_button_pressed(mut self, pressed: bool) -> Self {
        self.write_by_name(EgpwsElectricalHarness::GPWS_FLAP_OFF_KEY, pressed);
        self
    }

    fn flaps_3_button_pressed(mut self, pressed: bool) -> Self {
        self.write_by_name(EgpwsElectricalHarness::GPWS_FLAPS3_KEY, pressed);
        self
    }

    fn gpws_sys_button_pressed(mut self, pressed: bool) -> Self {
        self.write_by_name(EgpwsElectricalHarness::GPWS_SYS_OFF_KEY, pressed);
        self
    }

    fn set_ra_failure(&mut self, failed: bool) {
        self.command(|a| a.ra.set_failed(failed));
    }

    fn set_ils_failure(&mut self, failed: bool) {
        self.command(|a| a.ils.set_failed(failed));
    }

    fn get_aural_warning(&mut self) -> u8 {
        ReadByName::<EgpwcTestBed, u8>::read_by_name(
            self,
            EnhancedGroundProximityWarningComputer::AURAL_OUTPUT_KEY,
        )
    }

    fn get_audio_on(&self) -> bool {
        self.query(|ac: &TestAircraft| ac.egpwc.discrete_outputs().audio_on)
    }

    fn is_warning_light_on(&mut self) -> bool {
        self.query(|ac: &TestAircraft| ac.egpwc.discrete_outputs().warning_lamp)
    }

    fn is_alert_light_on(&mut self) -> bool {
        self.query(|ac: &TestAircraft| ac.egpwc.discrete_outputs().alert_lamp)
    }

    fn egpws_sys_fault(&mut self) -> bool {
        self.query(|ac: &TestAircraft| ac.egpwc.discrete_outputs().gpws_inop)
    }

    fn assert_no_warning_active(&mut self) {
        assert!(!self.get_audio_on());
        assert_eq!(self.get_aural_warning(), AuralWarning::None as u8);
        assert!(!self.is_warning_light_on());
        assert!(!self.is_alert_light_on());
    }
}
impl TestBed for EgpwcTestBed {
    type Aircraft = TestAircraft;

    fn test_bed(&self) -> &SimulationTestBed<TestAircraft> {
        &self.test_bed
    }

    fn test_bed_mut(&mut self) -> &mut SimulationTestBed<TestAircraft> {
        &mut self.test_bed
    }
}

fn test_bed() -> EgpwcTestBed {
    EgpwcTestBed::new()
}

fn test_bed_with() -> EgpwcTestBed {
    test_bed()
}

#[test]
fn self_tests_after_power_loss_on_ground_and_emits_no_warnings() {
    let mut test_bed = test_bed_with().on_ground().and().powered();
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();

    let mut test_bed = test_bed.no_power();
    test_bed.run_with_delta(Duration::from_millis(500));
    assert!(test_bed.egpws_sys_fault());
    let mut test_bed = test_bed.powered();
    test_bed.run_with_delta(Duration::from_millis(1_000));
    assert!(test_bed.egpws_sys_fault());
    test_bed.run_with_delta(Duration::from_millis(20_000));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();
}

#[test]
fn emits_failure_when_ra_is_failed() {
    let mut test_bed = test_bed_with()
        .altitude_of(Length::new::<foot>(2500.0))
        .and()
        .powered();

    test_bed.run_with_delta(Duration::from_millis(1));

    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();

    test_bed.set_ra_failure(true);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();

    test_bed.set_ra_failure(false);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();
}

#[test]
fn emits_no_failure_when_ils_is_failed_in_air() {
    let mut test_bed = test_bed_with()
        .altitude_of(Length::new::<foot>(2500.0))
        .and()
        .powered();

    test_bed.run_with_delta(Duration::from_millis(1));

    test_bed.set_ils_failure(true);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();

    test_bed.set_ils_failure(false);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();
}

#[test]
fn emits_failure_when_ils_is_failed_on_ground() {
    let mut test_bed = test_bed_with().on_ground().and().powered();

    test_bed.run_with_delta(Duration::from_millis(1));

    test_bed.set_ils_failure(true);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();

    test_bed.set_ils_failure(false);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(!test_bed.egpws_sys_fault());
    test_bed.assert_no_warning_active();
}

#[test]
fn mode_1_test() {
    let mut test_bed = test_bed_with()
        .altitude_of(Length::new::<foot>(1500.0))
        .terrain_height_of(Length::new::<foot>(0.0))
        .vertical_speed_of(Velocity::new::<foot_per_minute>(0.0))
        .cas_of(Velocity::new::<knot>(250.))
        .and()
        .powered();

    test_bed.run_with_delta(Duration::from_millis(1));
    test_bed.assert_no_warning_active();

    // Inside of alert area
    test_bed = test_bed.vertical_speed_of(Velocity::new::<foot_per_minute>(-4000.0));
    test_bed.run_with_delta(Duration::from_millis(1));
    // Confirm time not elapsed
    test_bed.assert_no_warning_active();
    test_bed.run_with_delta(Duration::from_millis(1_000));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::SinkRate as u8); // Emission pattern depends on audio declutter active
    assert!(test_bed.is_warning_light_on());

    // Inside Warning area
    test_bed = test_bed.vertical_speed_of(Velocity::new::<foot_per_minute>(-5000.0));
    test_bed.run_with_delta(Duration::from_millis(1_700));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::PullUp as u8);
    assert!(test_bed.is_warning_light_on());

    // Warning immediately ceases with GPWS SYS OFF pressed
    test_bed = test_bed.gpws_sys_button_pressed(true);
    test_bed.run_with_delta(Duration::from_millis(1));
    test_bed.assert_no_warning_active();

    // Warning immediately restarts with GPWS SYS OFF no longer pressed
    test_bed = test_bed.gpws_sys_button_pressed(false);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::PullUp as u8);
    assert!(test_bed.is_warning_light_on());

    // Exiting warning area
    test_bed = test_bed.vertical_speed_of(Velocity::new::<foot_per_minute>(-1000.0));
    test_bed.run_with_delta(Duration::from_millis(100));

    // Confirm time not elapsed
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::PullUp as u8);
    assert!(test_bed.is_warning_light_on());

    test_bed.run_with_delta(Duration::from_millis(200));
    test_bed.assert_no_warning_active();
}

#[test]
fn mode_2_a_test() {
    let mut test_bed = test_bed_with()
        .altitude_of(Length::new::<foot>(2500.0))
        .terrain_height_of(Length::new::<foot>(0.0))
        .vertical_speed_of(Velocity::new::<foot_per_minute>(0.0))
        .cas_of(Velocity::new::<knot>(310.0))
        .and()
        .powered();

    // Step 71s, since Mode 4B is active for 60s after takeoff and flight mode is activated 10s after above 30ft RA
    // since pitch angle is not set above for immediate switching to occur.
    test_bed.run_with_delta(Duration::from_millis(1_000));
    test_bed.run_with_delta(Duration::from_millis(70_000));
    test_bed.assert_no_warning_active();

    // Terrain rises
    test_bed = test_bed.terrain_height_of(Length::new::<foot>(1000.0));
    test_bed.run_with_delta(Duration::from_millis(3_000));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::Terrain as u8); // Emission pattern depends on audio declutter active
    assert!(test_bed.is_warning_light_on());

    // Warning immediately ceases with GPWS SYS OFF pressed
    test_bed = test_bed.gpws_sys_button_pressed(true);
    test_bed.run_with_delta(Duration::from_millis(1));
    test_bed.assert_no_warning_active();

    // Warning immediately restarts with GPWS SYS OFF no longer pressed
    test_bed = test_bed.gpws_sys_button_pressed(false);
    test_bed.run_with_delta(Duration::from_millis(1));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::Terrain as u8);
    assert!(test_bed.is_warning_light_on());

    test_bed = test_bed.cas_of(Velocity::new::<knot>(230.0));
    test_bed = test_bed.terrain_height_of(Length::new::<foot>(1125.0));
    test_bed.run_with_delta(Duration::from_millis(1_000));

    // Closure rate still 7500 ft/min, now at 1000 ft RA
    test_bed = test_bed.cas_of(Velocity::new::<knot>(230.0));
    test_bed = test_bed.terrain_height_of(Length::new::<foot>(1500.0));
    test_bed.run_with_delta(Duration::from_millis(3_000));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::Terrain as u8);
    assert!(test_bed.is_warning_light_on());

    // After two emissions of TERRAIN (ca. 2s), it will switch to PULL UP. Now closure rate is 2400 ft/min, at 800 ft RA
    test_bed = test_bed.terrain_height_of(Length::new::<foot>(1700.0));
    test_bed.run_with_delta(Duration::from_millis(5_000));
    assert!(test_bed.get_audio_on());
    assert_eq!(test_bed.get_aural_warning(), AuralWarning::PullUp as u8);
    assert!(test_bed.is_warning_light_on());

    // Exiting warning area due to lowering terrain. Now at 1000ft, since otherwise the Mode 4 warning would trigger.
    test_bed = test_bed.terrain_height_of(Length::new::<foot>(1500.0));
    test_bed.run_with_delta(Duration::from_millis(2_000));
    test_bed.assert_no_warning_active();
}
