// Copyright (c) 2021-2023 FlyByWire Simulations
//
// SPDX-License-Identifier: GPL-3.0

import { SimVarDefinition, SimVarValueType } from '@microsoft/msfs-sdk';
import { ArincEventBus } from '@flybywiresim/fbw-sdk';

import {
  AdirsSimVarDefinitions,
  AdirsSimVars,
  SwitchingPanelSimVarsDefinitions,
  SwitchingPanelVSimVars,
} from '../../MsfsAvionicsCommon/SimVarTypes';
import { UpdatableSimVarPublisher } from '../../MsfsAvionicsCommon/UpdatableSimVarPublisher';

export type PFDSimvars = AdirsSimVars &
  SwitchingPanelVSimVars & {
    coldDark: number;
    elec: boolean;
    elecFo: boolean;
    potentiometerCaptain: number;
    potentiometerFo: number;
    pitch: number;
    roll: number;
    // FIXME these two need ADR switching and per-side switching for baro with SwitchableSimVarProvider
    baroCorrectedAltitude: number;
    pressureAltitude: number;
    speed: number;
    noseGearCompressed: boolean;
    leftMainGearCompressed: boolean;
    rightMainGearCompressed: boolean;
    attHdgKnob: number;
    airKnob: number;
    vsBaro: number;
    vsInert: number;
    v1: number;
    vr: number;
    fwcFlightPhase: number;
    fmgcFlightPhase: number;
    hasLoc: boolean;
    hasDme: boolean;
    navIdent: string;
    navFreq: number;
    dme: number;
    navRadialError: number;
    hasGlideslope: boolean;
    glideSlopeError: number;
    markerBeacon: number;
    flapHandleIndex: number;
    aoa: number;
    ilsCourse: number;
    tla1: number;
    tla2: number;
    landingElevation: number;
    engOneRunning: boolean;
    engTwoRunning: boolean;
    setHoldSpeed: boolean;
    tdReached: boolean;
    checkSpeedMode: boolean;
    radioAltitude1: number;
    radioAltitude2: number;
    flexTemp: number;
    autoBrakeMode: number;
    autoBrakeActive: boolean;
    autoBrakeDecel: boolean;
    fpaRaw: number;
    daRaw: number;
    latAccRaw: number;
    fcdc1DiscreteWord1Raw: number;
    fcdc2DiscreteWord1Raw: number;
    fcdc1DiscreteWord2Raw: number;
    fcdc2DiscreteWord2Raw: number;
    fcdc1CaptPitchCommandRaw: number;
    fcdc2CaptPitchCommandRaw: number;
    fcdc1FoPitchCommandRaw: number;
    fcdc2FoPitchCommandRaw: number;
    fcdc1CaptRollCommandRaw: number;
    fcdc2CaptRollCommandRaw: number;
    fcdc1FoRollCommandRaw: number;
    fcdc2FoRollCommandRaw: number;
    xtk: number;
    ldevRequestLeft: boolean;
    ldevRequestRight: boolean;
    vdev: number;
    landingElevation1Raw: number;
    landingElevation2Raw: number;
    fac1Healthy: boolean;
    fac2Healthy: boolean;
    fac1VAlphaProtRaw: number;
    fac2VAlphaProtRaw: number;
    fac1VAlphaMaxRaw: number;
    fac2VAlphaMaxRaw: number;
    fac1VStallWarnRaw: number;
    fac2VStallWarnRaw: number;
    fac1VMaxRaw: number;
    fac2VMaxRaw: number;
    fac1VFeNextRaw: number;
    fac2VFeNextRaw: number;
    fac1VCTrendRaw: number;
    fac2VCTrendRaw: number;
    fac1VManRaw: number;
    fac2VManRaw: number;
    fac1V4Raw: number;
    fac2V4Raw: number;
    fac1V3Raw: number;
    fac2V3Raw: number;
    fac1VLsRaw: number;
    fac2VLsRaw: number;
    fac1EstimatedBetaRaw: number;
    fac2EstimatedBetaRaw: number;
    fac1BetaTargetRaw: number;
    fac2BetaTargetRaw: number;
    irMaintWordRaw: number;
    slatPosLeft: number;
    fm1NavDiscrete: number;
    fm1EisDiscrete2Raw: number;
    fm2EisDiscrete2Raw: number;
    fm1MdaRaw: number;
    fm2MdaRaw: number;
    fm1DhRaw: number;
    fm2DhRaw: number;
    fm1HealthyDiscrete: number;
    fm2HealthyDiscrete: number;
    fm1TransAltRaw: number;
    fm2TransAltRaw: number;
    fm1TransLvlRaw: number;
    fm2TransLvlRaw: number;
    fm1Backbeam: boolean;
    fm2Backbeam: boolean;
    ecu1MaintenanceWord6Raw: number;
    ecu2MaintenanceWord6Raw: number;
  };

export enum PFDVars {
  coldDark = 'L:A32NX_COLD_AND_DARK_SPAWN',
  elec = 'L:A32NX_ELEC_AC_ESS_BUS_IS_POWERED',
  elecFo = 'L:A32NX_ELEC_AC_2_BUS_IS_POWERED',
  potentiometerCaptain = 'LIGHT POTENTIOMETER:88',
  potentiometerFo = 'LIGHT POTENTIOMETER:90',
  pitch = 'L:A32NX_ADIRS_IR_1_PITCH',
  roll = 'L:A32NX_ADIRS_IR_1_ROLL',
  magHeadingRaw = 'L:A32NX_ADIRS_IR_1_HEADING',
  baroCorrectedAltitude1 = 'L:A32NX_ADIRS_ADR_1_BARO_CORRECTED_ALTITUDE_1',
  pressureAltitude = 'L:A32NX_ADIRS_ADR_1_ALTITUDE',
  speed = 'L:A32NX_ADIRS_ADR_1_COMPUTED_AIRSPEED',
  noseGearCompressed = 'L:A32NX_LGCIU_1_NOSE_GEAR_COMPRESSED',
  leftMainGearCompressed = 'L:A32NX_LGCIU_1_LEFT_GEAR_COMPRESSED',
  rightMainGearCompressed = 'L:A32NX_LGCIU_1_RIGHT_GEAR_COMPRESSED',
  attHdgKnob = 'L:A32NX_ATT_HDG_SWITCHING_KNOB',
  airKnob = 'L:A32NX_AIR_DATA_SWITCHING_KNOB',
  vsBaro = 'L:A32NX_ADIRS_ADR_1_BAROMETRIC_VERTICAL_SPEED',
  vsInert = 'L:A32NX_ADIRS_IR_1_VERTICAL_SPEED',
  v1 = 'L:AIRLINER_V1_SPEED',
  vr = 'L:AIRLINER_VR_SPEED',
  fwcFlightPhase = 'L:A32NX_FWC_FLIGHT_PHASE',
  fmgcFlightPhase = 'L:A32NX_FMGC_FLIGHT_PHASE',
  hasLoc = 'L:A32NX_RADIO_RECEIVER_LOC_IS_VALID',
  hasDme = 'NAV HAS DME:3',
  navIdent = 'NAV IDENT:3',
  navFreq = 'NAV ACTIVE FREQUENCY:3',
  dme = 'NAV DME:3',
  navRadialError = 'L:A32NX_RADIO_RECEIVER_LOC_DEVIATION',
  hasGlideslope = 'L:A32NX_RADIO_RECEIVER_GS_IS_VALID',
  glideSlopeError = 'L:A32NX_RADIO_RECEIVER_GS_DEVIATION',
  markerBeacon = 'MARKER BEACON STATE',
  mach = 'L:A32NX_ADIRS_ADR_1_MACH',
  flapHandleIndex = 'L:A32NX_FLAPS_HANDLE_INDEX',
  magTrackRaw = 'L:A32NX_ADIRS_IR_1_TRACK',
  aoa = 'INCIDENCE ALPHA',
  ilsCourse = 'L:A32NX_FM_LS_COURSE',
  tla1 = 'L:A32NX_AUTOTHRUST_TLA:1',
  tla2 = 'L:A32NX_AUTOTHRUST_TLA:2',
  engOneRunning = 'GENERAL ENG COMBUSTION:1',
  engTwoRunning = 'GENERAL ENG COMBUSTION:2',
  setHoldSpeed = 'L:A32NX_PFD_MSG_SET_HOLD_SPEED',
  tdReached = 'L:A32NX_PFD_MSG_TD_REACHED',
  checkSpeedMode = 'L:A32NX_PFD_MSG_CHECK_SPEED_MODE',
  radioAltitude1 = 'L:A32NX_RA_1_RADIO_ALTITUDE',
  radioAltitude2 = 'L:A32NX_RA_2_RADIO_ALTITUDE',
  flexTemp = 'L:A32NX_AIRLINER_TO_FLEX_TEMP',
  autoBrakeMode = 'L:A32NX_AUTOBRAKES_ARMED_MODE',
  autoBrakeActive = 'L:A32NX_AUTOBRAKES_ACTIVE',
  autoBrakeDecel = 'L:A32NX_AUTOBRAKES_DECEL_LIGHT',
  fpaRaw = 'L:A32NX_ADIRS_IR_1_FLIGHT_PATH_ANGLE',
  daRaw = 'L:A32NX_ADIRS_IR_1_DRIFT_ANGLE',
  latAccRaw = 'L:A32NX_ADIRS_IR_1_BODY_LATERAL_ACC',
  fcdc1DiscreteWord1Raw = 'L:A32NX_FCDC_1_DISCRETE_WORD_1',
  fcdc2DiscreteWord1Raw = 'L:A32NX_FCDC_2_DISCRETE_WORD_1',
  fcdc1DiscreteWord2Raw = 'L:A32NX_FCDC_1_DISCRETE_WORD_2',
  fcdc2DiscreteWord2Raw = 'L:A32NX_FCDC_2_DISCRETE_WORD_2',
  fcdc1CaptPitchCommandRaw = 'L:A32NX_FCDC_1_CAPT_PITCH_COMMAND',
  fcdc2CaptPitchCommandRaw = 'L:A32NX_FCDC_2_CAPT_PITCH_COMMAND',
  fcdc1FoPitchCommandRaw = 'L:A32NX_FCDC_1_FO_PITCH_COMMAND',
  fcdc2FoPitchCommandRaw = 'L:A32NX_FCDC_2_FO_PITCH_COMMAND',
  fcdc1CaptRollCommandRaw = 'L:A32NX_FCDC_1_CAPT_ROLL_COMMAND',
  fcdc2CaptRollCommandRaw = 'L:A32NX_FCDC_2_CAPT_ROLL_COMMAND',
  fcdc1FoRollCommandRaw = 'L:A32NX_FCDC_1_FO_ROLL_COMMAND',
  fcdc2FoRollCommandRaw = 'L:A32NX_FCDC_2_FO_ROLL_COMMAND',
  xtk = 'L:A32NX_FG_CROSS_TRACK_ERROR',
  ldevLeft = 'L:A32NX_FMGC_L_LDEV_REQUEST',
  ldevRight = 'L:A32NX_FMGC_R_LDEV_REQUEST',
  vdev = 'L:A32NX_FM_VDEV',
  landingElevation1Raw = 'L:A32NX_FM1_LANDING_ELEVATION',
  landingElevation2Raw = 'L:A32NX_FM2_LANDING_ELEVATION',
  fac1Healthy = 'L:A32NX_FAC_1_HEALTHY',
  fac2Healthy = 'L:A32NX_FAC_2_HEALTHY',
  fac1VAlphaProtRaw = 'L:A32NX_FAC_1_V_ALPHA_PROT',
  fac2VAlphaProtRaw = 'L:A32NX_FAC_2_V_ALPHA_PROT',
  fac1VAlphaMaxRaw = 'L:A32NX_FAC_1_V_ALPHA_LIM',
  fac2VAlphaMaxRaw = 'L:A32NX_FAC_2_V_ALPHA_LIM',
  fac1VStallWarnRaw = 'L:A32NX_FAC_1_V_STALL_WARN',
  fac2VStallWarnRaw = 'L:A32NX_FAC_2_V_STALL_WARN',
  fac1VMaxRaw = 'L:A32NX_FAC_1_V_MAX',
  fac2VMaxRaw = 'L:A32NX_FAC_2_V_MAX',
  fac1VFeNextRaw = 'L:A32NX_FAC_1_V_FE_NEXT',
  fac2VFeNextRaw = 'L:A32NX_FAC_2_V_FE_NEXT',
  fac1VCTrendRaw = 'L:A32NX_FAC_1_SPEED_TREND',
  fac2VCTrendRaw = 'L:A32NX_FAC_2_SPEED_TREND',
  fac1VManRaw = 'L:A32NX_FAC_1_V_MAN',
  fac2VManRaw = 'L:A32NX_FAC_2_V_MAN',
  fac1V4Raw = 'L:A32NX_FAC_1_V_4',
  fac2V4Raw = 'L:A32NX_FAC_2_V_4',
  fac1V3Raw = 'L:A32NX_FAC_1_V_3',
  fac2V3Raw = 'L:A32NX_FAC_2_V_3',
  fac1VLsRaw = 'L:A32NX_FAC_1_V_LS',
  fac2VLsRaw = 'L:A32NX_FAC_2_V_LS',
  fac1EstimatedBetaRaw = 'L:A32NX_FAC_1_ESTIMATED_SIDESLIP',
  fac2EstimatedBetaRaw = 'L:A32NX_FAC_2_ESTIMATED_SIDESLIP',
  fac1BetaTargetRaw = 'L:A32NX_FAC_1_SIDESLIP_TARGET',
  fac2BetaTargetRaw = 'L:A32NX_FAC_2_SIDESLIP_TARGET',
  irMaintWordRaw = 'L:A32NX_ADIRS_IR_1_MAINT_WORD',
  trueHeadingRaw = 'L:A32NX_ADIRS_IR_1_TRUE_HEADING',
  trueTrackRaw = 'L:A32NX_ADIRS_IR_1_TRUE_TRACK',
  slatPosLeft = 'L:A32NX_LEFT_SLATS_ANGLE',
  fm1NavDiscrete = 'L:A32NX_FM1_NAV_DISCRETE',
  fm1EisDiscrete2 = 'L:A32NX_FM1_EIS_DISCRETE_WORD_2',
  fm2EisDiscrete2 = 'L:A32NX_FM2_EIS_DISCRETE_WORD_2',
  fm1MdaRaw = 'L:A32NX_FM1_MINIMUM_DESCENT_ALTITUDE',
  fm2MdaRaw = 'L:A32NX_FM2_MINIMUM_DESCENT_ALTITUDE',
  fm1DhRaw = 'L:A32NX_FM1_DECISION_HEIGHT',
  fm2DhRaw = 'L:A32NX_FM1_DECISION_HEIGHT',
  fm1HealthyDiscrete = 'L:A32NX_FM1_HEALTHY_DISCRETE',
  fm2HealthyDiscrete = 'L:A32NX_FM2_HEALTHY_DISCRETE',
  fm1TransAltRaw = 'L:A32NX_FM1_TRANS_ALT',
  fm2TransAltRaw = 'L:A32NX_FM2_TRANS_ALT',
  fm1TransLvlRaw = 'L:A32NX_FM1_TRANS_LVL',
  fm2TransLvlRaw = 'L:A32NX_FM2_TRANS_LVL',
  fm1Backbeam = 'L:A32NX_FM1_BACKBEAM_SELECTED',
  fm2Backbeam = 'L:A32NX_FM2_BACKBEAM_SELECTED',
  ecu1MaintenanceWord6Raw = 'L:A32NX_ECU_1_MAINTENANCE_WORD_6',
  ecu2MaintenanceWord6Raw = 'L:A32NX_ECU_2_MAINTENANCE_WORD_6',
}

/** A publisher to poll and publish nav/com simvars. */
export class PFDSimvarPublisher extends UpdatableSimVarPublisher<PFDSimvars> {
  private static simvars = new Map<keyof PFDSimvars, SimVarDefinition>([
    ...AdirsSimVarDefinitions,
    ...SwitchingPanelSimVarsDefinitions,
    ['coldDark', { name: PFDVars.coldDark, type: SimVarValueType.Number }],
    ['elec', { name: PFDVars.elec, type: SimVarValueType.Bool }],
    ['elecFo', { name: PFDVars.elecFo, type: SimVarValueType.Bool }],
    ['potentiometerCaptain', { name: PFDVars.potentiometerCaptain, type: SimVarValueType.Number }],
    ['potentiometerFo', { name: PFDVars.potentiometerFo, type: SimVarValueType.Number }],
    ['pitch', { name: PFDVars.pitch, type: SimVarValueType.Number }],
    ['roll', { name: PFDVars.roll, type: SimVarValueType.Number }],
    ['baroCorrectedAltitude', { name: PFDVars.baroCorrectedAltitude1, type: SimVarValueType.Number }],
    ['pressureAltitude', { name: PFDVars.pressureAltitude, type: SimVarValueType.Number }],
    ['speed', { name: PFDVars.speed, type: SimVarValueType.Number }],
    ['noseGearCompressed', { name: PFDVars.noseGearCompressed, type: SimVarValueType.Bool }],
    ['leftMainGearCompressed', { name: PFDVars.leftMainGearCompressed, type: SimVarValueType.Bool }],
    ['rightMainGearCompressed', { name: PFDVars.rightMainGearCompressed, type: SimVarValueType.Bool }],
    ['attHdgKnob', { name: PFDVars.attHdgKnob, type: SimVarValueType.Enum }],
    ['airKnob', { name: PFDVars.airKnob, type: SimVarValueType.Enum }],
    ['vsBaro', { name: PFDVars.vsBaro, type: SimVarValueType.Number }],
    ['vsInert', { name: PFDVars.vsInert, type: SimVarValueType.Number }],
    ['v1', { name: PFDVars.v1, type: SimVarValueType.Knots }],
    ['vr', { name: PFDVars.vr, type: SimVarValueType.Knots }],
    ['fwcFlightPhase', { name: PFDVars.fwcFlightPhase, type: SimVarValueType.Number }],
    ['fmgcFlightPhase', { name: PFDVars.fmgcFlightPhase, type: SimVarValueType.Enum }],
    ['hasLoc', { name: PFDVars.hasLoc, type: SimVarValueType.Bool }],
    ['hasDme', { name: PFDVars.hasDme, type: SimVarValueType.Bool }],
    ['navIdent', { name: PFDVars.navIdent, type: SimVarValueType.String }],
    ['navFreq', { name: PFDVars.navFreq, type: SimVarValueType.MHz }],
    ['dme', { name: PFDVars.dme, type: SimVarValueType.NM }],
    ['navRadialError', { name: PFDVars.navRadialError, type: SimVarValueType.Degree }],
    ['hasGlideslope', { name: PFDVars.hasGlideslope, type: SimVarValueType.Bool }],
    ['glideSlopeError', { name: PFDVars.glideSlopeError, type: SimVarValueType.Degree }],
    ['markerBeacon', { name: PFDVars.markerBeacon, type: SimVarValueType.Enum }],
    ['mach', { name: PFDVars.mach, type: SimVarValueType.Number }],
    ['flapHandleIndex', { name: PFDVars.flapHandleIndex, type: SimVarValueType.Number }],
    ['magTrackRaw', { name: PFDVars.magTrackRaw, type: SimVarValueType.Number }],
    ['aoa', { name: PFDVars.aoa, type: SimVarValueType.Degree }],
    ['ilsCourse', { name: PFDVars.ilsCourse, type: SimVarValueType.Number }],
    ['tla1', { name: PFDVars.tla1, type: SimVarValueType.Number }],
    ['tla2', { name: PFDVars.tla2, type: SimVarValueType.Number }],
    ['engOneRunning', { name: PFDVars.engOneRunning, type: SimVarValueType.Bool }],
    ['engTwoRunning', { name: PFDVars.engTwoRunning, type: SimVarValueType.Bool }],
    ['setHoldSpeed', { name: PFDVars.setHoldSpeed, type: SimVarValueType.Bool }],
    ['tdReached', { name: PFDVars.tdReached, type: SimVarValueType.Bool }],
    ['checkSpeedMode', { name: PFDVars.checkSpeedMode, type: SimVarValueType.Bool }],
    ['radioAltitude1', { name: PFDVars.radioAltitude1, type: SimVarValueType.Number }],
    ['radioAltitude2', { name: PFDVars.radioAltitude2, type: SimVarValueType.Number }],
    ['flexTemp', { name: PFDVars.flexTemp, type: SimVarValueType.Number }],
    ['autoBrakeMode', { name: PFDVars.autoBrakeMode, type: SimVarValueType.Number }],
    ['autoBrakeActive', { name: PFDVars.autoBrakeActive, type: SimVarValueType.Bool }],
    ['autoBrakeDecel', { name: PFDVars.autoBrakeDecel, type: SimVarValueType.Bool }],
    ['fpaRaw', { name: PFDVars.fpaRaw, type: SimVarValueType.Number }],
    ['daRaw', { name: PFDVars.daRaw, type: SimVarValueType.Number }],
    ['latAccRaw', { name: PFDVars.latAccRaw, type: SimVarValueType.Number }],
    ['fcdc1DiscreteWord1Raw', { name: PFDVars.fcdc1DiscreteWord1Raw, type: SimVarValueType.Number }],
    ['fcdc2DiscreteWord1Raw', { name: PFDVars.fcdc2DiscreteWord1Raw, type: SimVarValueType.Number }],
    ['fcdc1DiscreteWord2Raw', { name: PFDVars.fcdc1DiscreteWord2Raw, type: SimVarValueType.Number }],
    ['fcdc2DiscreteWord2Raw', { name: PFDVars.fcdc2DiscreteWord2Raw, type: SimVarValueType.Number }],
    ['fcdc1CaptPitchCommandRaw', { name: PFDVars.fcdc1CaptPitchCommandRaw, type: SimVarValueType.Number }],
    ['fcdc2CaptPitchCommandRaw', { name: PFDVars.fcdc2CaptPitchCommandRaw, type: SimVarValueType.Number }],
    ['fcdc1FoPitchCommandRaw', { name: PFDVars.fcdc1FoPitchCommandRaw, type: SimVarValueType.Number }],
    ['fcdc2FoPitchCommandRaw', { name: PFDVars.fcdc2FoPitchCommandRaw, type: SimVarValueType.Number }],
    ['fcdc1CaptRollCommandRaw', { name: PFDVars.fcdc1CaptRollCommandRaw, type: SimVarValueType.Number }],
    ['fcdc2CaptRollCommandRaw', { name: PFDVars.fcdc2CaptRollCommandRaw, type: SimVarValueType.Number }],
    ['fcdc1FoRollCommandRaw', { name: PFDVars.fcdc1FoRollCommandRaw, type: SimVarValueType.Number }],
    ['fcdc2FoRollCommandRaw', { name: PFDVars.fcdc2FoRollCommandRaw, type: SimVarValueType.Number }],
    ['xtk', { name: PFDVars.xtk, type: SimVarValueType.NM }],
    ['ldevRequestLeft', { name: PFDVars.ldevLeft, type: SimVarValueType.Bool }],
    ['ldevRequestRight', { name: PFDVars.ldevRight, type: SimVarValueType.Bool }],
    ['vdev', { name: PFDVars.vdev, type: SimVarValueType.Number }],
    ['landingElevation1Raw', { name: PFDVars.landingElevation1Raw, type: SimVarValueType.Number }],
    ['landingElevation2Raw', { name: PFDVars.landingElevation2Raw, type: SimVarValueType.Number }],
    ['fac1Healthy', { name: PFDVars.fac1Healthy, type: SimVarValueType.Bool }],
    ['fac2Healthy', { name: PFDVars.fac2Healthy, type: SimVarValueType.Bool }],
    ['fac1VAlphaProtRaw', { name: PFDVars.fac1VAlphaProtRaw, type: SimVarValueType.Number }],
    ['fac2VAlphaProtRaw', { name: PFDVars.fac2VAlphaProtRaw, type: SimVarValueType.Number }],
    ['fac1VAlphaMaxRaw', { name: PFDVars.fac1VAlphaMaxRaw, type: SimVarValueType.Number }],
    ['fac2VAlphaMaxRaw', { name: PFDVars.fac2VAlphaMaxRaw, type: SimVarValueType.Number }],
    ['fac1VStallWarnRaw', { name: PFDVars.fac1VStallWarnRaw, type: SimVarValueType.Number }],
    ['fac2VStallWarnRaw', { name: PFDVars.fac2VStallWarnRaw, type: SimVarValueType.Number }],
    ['fac1VMaxRaw', { name: PFDVars.fac1VMaxRaw, type: SimVarValueType.Number }],
    ['fac2VMaxRaw', { name: PFDVars.fac2VMaxRaw, type: SimVarValueType.Number }],
    ['fac1VFeNextRaw', { name: PFDVars.fac1VFeNextRaw, type: SimVarValueType.Number }],
    ['fac2VFeNextRaw', { name: PFDVars.fac2VFeNextRaw, type: SimVarValueType.Number }],
    ['fac1VCTrendRaw', { name: PFDVars.fac1VCTrendRaw, type: SimVarValueType.Number }],
    ['fac2VCTrendRaw', { name: PFDVars.fac2VCTrendRaw, type: SimVarValueType.Number }],
    ['fac1VManRaw', { name: PFDVars.fac1VManRaw, type: SimVarValueType.Number }],
    ['fac2VManRaw', { name: PFDVars.fac2VManRaw, type: SimVarValueType.Number }],
    ['fac1V4Raw', { name: PFDVars.fac1V4Raw, type: SimVarValueType.Number }],
    ['fac2V4Raw', { name: PFDVars.fac2V4Raw, type: SimVarValueType.Number }],
    ['fac1V3Raw', { name: PFDVars.fac1V3Raw, type: SimVarValueType.Number }],
    ['fac2V3Raw', { name: PFDVars.fac2V3Raw, type: SimVarValueType.Number }],
    ['fac1VLsRaw', { name: PFDVars.fac1VLsRaw, type: SimVarValueType.Number }],
    ['fac2VLsRaw', { name: PFDVars.fac2VLsRaw, type: SimVarValueType.Number }],
    ['fac1EstimatedBetaRaw', { name: PFDVars.fac1EstimatedBetaRaw, type: SimVarValueType.Number }],
    ['fac2EstimatedBetaRaw', { name: PFDVars.fac2EstimatedBetaRaw, type: SimVarValueType.Number }],
    ['fac1BetaTargetRaw', { name: PFDVars.fac1BetaTargetRaw, type: SimVarValueType.Number }],
    ['fac2BetaTargetRaw', { name: PFDVars.fac2BetaTargetRaw, type: SimVarValueType.Number }],
    ['irMaintWordRaw', { name: PFDVars.irMaintWordRaw, type: SimVarValueType.Number }],
    ['slatPosLeft', { name: PFDVars.slatPosLeft, type: SimVarValueType.Number }],
    ['fm1NavDiscrete', { name: PFDVars.fm1NavDiscrete, type: SimVarValueType.Number }],
    ['fm1EisDiscrete2Raw', { name: PFDVars.fm1EisDiscrete2, type: SimVarValueType.Number }],
    ['fm2EisDiscrete2Raw', { name: PFDVars.fm2EisDiscrete2, type: SimVarValueType.Number }],
    ['fm1MdaRaw', { name: PFDVars.fm1MdaRaw, type: SimVarValueType.Number }],
    ['fm2MdaRaw', { name: PFDVars.fm2MdaRaw, type: SimVarValueType.Number }],
    ['fm1DhRaw', { name: PFDVars.fm1DhRaw, type: SimVarValueType.Number }],
    ['fm2DhRaw', { name: PFDVars.fm2DhRaw, type: SimVarValueType.Number }],
    ['fm1HealthyDiscrete', { name: PFDVars.fm1HealthyDiscrete, type: SimVarValueType.Number }],
    ['fm2HealthyDiscrete', { name: PFDVars.fm2HealthyDiscrete, type: SimVarValueType.Number }],
    ['fm1TransAltRaw', { name: PFDVars.fm1TransAltRaw, type: SimVarValueType.Number }],
    ['fm2TransAltRaw', { name: PFDVars.fm2TransAltRaw, type: SimVarValueType.Number }],
    ['fm1TransLvlRaw', { name: PFDVars.fm1TransLvlRaw, type: SimVarValueType.Number }],
    ['fm2TransLvlRaw', { name: PFDVars.fm2TransLvlRaw, type: SimVarValueType.Number }],
    ['fm1Backbeam', { name: PFDVars.fm1Backbeam, type: SimVarValueType.Bool }],
    ['fm2Backbeam', { name: PFDVars.fm2Backbeam, type: SimVarValueType.Bool }],
    ['ecu1MaintenanceWord6Raw', { name: PFDVars.ecu1MaintenanceWord6Raw, type: SimVarValueType.Number }],
    ['ecu2MaintenanceWord6Raw', { name: PFDVars.ecu2MaintenanceWord6Raw, type: SimVarValueType.Number }],
  ]);

  public constructor(bus: ArincEventBus) {
    super(PFDSimvarPublisher.simvars, bus);
  }
}
