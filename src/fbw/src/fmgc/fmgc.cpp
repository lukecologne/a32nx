#include "fmgc.h"
#include <iostream>

Fmgc::Fmgc(bool isSide1) : side1(isSide1) {}

void Fmgc::init() {}

void Fmgc::step(double deltaTime, double simulationTime, bool isPowered) {
  monitorAdirsValidity();
  monitorRaValidity();
  monitorFacValidity();
  monitorIlsValidity();

  computeApFdAthrConditions();

  computeAthrEngagement(deltaTime);
  computeFdEngagement(deltaTime);
  computeApEngagement(deltaTime);

  computeLandingCapability();
};

void Fmgc::monitorAdirsValidity() {
  adrOwnInvalid = anyAdrBusWordInvalid(busInputs.adirsOwn.adrBus);
  irOwnInvalid = anyIrBusWordInvalid(busInputs.adirsOwn.irsBus);

  adrOppInvalid = anyAdrBusWordInvalid(busInputs.adirsOpp.adrBus);
  irOppInvalid = anyIrBusWordInvalid(busInputs.adirsOpp.irsBus);

  adr3Invalid = anyAdrBusWordInvalid(busInputs.adirs3.adrBus);
  ir3Invalid = anyIrBusWordInvalid(busInputs.adirs3.irsBus);

  dualAdrFailure = (adrOwnInvalid && adrOppInvalid) || (adrOwnInvalid && adr3Invalid) || (adrOppInvalid && adr3Invalid);
  dualIrFailure = (irOwnInvalid && irOppInvalid) || (irOwnInvalid && ir3Invalid) || (irOppInvalid && ir3Invalid);

  if (adrOwnInvalid || discreteInputs.adc3Switch) {
    adrBus = busInputs.adirs3.adrBus;
  } else {
    adrBus = busInputs.adirsOwn.adrBus;
  }

  if (irOwnInvalid || discreteInputs.ir3Switch) {
    irBus = busInputs.adirs3.irsBus;
  } else {
    irBus = busInputs.adirsOwn.irsBus;
  }
};

void Fmgc::monitorRaValidity() {
  raOwnInvalid = busInputs.raOwn.radioHeight.isFw();
  raOppInvalid = busInputs.raOpp.radioHeight.isFw();

  if (raOwnInvalid) {
    raBus = busInputs.raOpp;
  } else {
    raBus = busInputs.raOwn;
  }
}

void Fmgc::monitorFacValidity() {
  if (discreteInputs.facOwnHealthy) {
    facBus = busInputs.facOwn;
  } else if (discreteInputs.facOppHealthy) {
    facBus = busInputs.facOpp;
  }

  facOwnInvalid = busInputs.facOwn.discreteWord4.isFw();
  facOppInvalid = busInputs.facOpp.discreteWord4.isFw();

  bool alphaFloorOwn = busInputs.facOwn.discreteWord4.bitFromValue(29);
  bool alphaFloorOpp = busInputs.facOpp.discreteWord4.bitFromValue(29);

  alphaFloorCondition = (!discreteInputs.facOwnHealthy || alphaFloorOwn) &&
                        (discreteInputs.facOwnHealthy || discreteInputs.facOppHealthy) && (!discreteInputs.facOppHealthy || alphaFloorOpp);
}

void Fmgc::monitorIlsValidity() {
  ilsOwnInvalid = busInputs.ilsOwn.locDeviation.isFw();
  ilsOppInvalid = busInputs.ilsOpp.locDeviation.isFw();

  if (ilsOwnInvalid) {
    ilsBus = busInputs.ilsOpp;
  } else {
    ilsBus = busInputs.ilsOwn;
  }
}

// TODO add remaining conditions (needs FAC, FM validity, ILS, RA, etc. implementations )
void Fmgc::computeApFdAthrConditions() {
  apFdAthrCommonCondition = !dualAdrFailure && !dualIrFailure;

  // Just check one label, should be fine because if one label is FW every other should be too
  bool fcuBusValid = !busInputs.fcuOwn.fcuDiscreteWord1.isFw();

  bool isGsArmed = static_cast<unsigned long long>(autopilotStateMachineOutput.vertical_mode_armed) >> 4 & 0x01;
  bool isGsEngaged = autopilotStateMachineOutput.vertical_mode >= 30 && autopilotStateMachineOutput.vertical_mode <= 34;

  apFdCommonCondition = true;  //!(dualRaFailure && (isGsArmed || isGsEngaged)) && fcuBusValid;
};

void Fmgc::computeFdEngagement(double deltaTime) {
  bool fdOffOwn = busInputs.fcuOwn.fcuDiscreteWord2.bitFromValue(side1 ? 26 : 27);

  bool fdOffOpp = busInputs.fcuOwn.fcuDiscreteWord2.bitFromValue(side1 ? 27 : 26);

  bool fdEngageCondition = !(fdOffOwn && (fdOffOpp || discreteInputs.fdOppEngaged));
  isFdEngaged = fdEngagedConfirmNode.update(apFdCommonCondition && apFdAthrCommonCondition && fdEngageCondition, deltaTime);
};

void Fmgc::computeApEngagement(double deltaTime) {
  auto activeLatMode = autopilotStateMachineOutput.lateral_mode;
  bool isLocArmed = static_cast<unsigned long long>(autopilotStateMachineOutput.lateral_mode_armed) >> 1 & 0x01;
  bool isLocEngaged = activeLatMode >= 30 && activeLatMode <= 34;
  auto activeVertMode = autopilotStateMachineOutput.vertical_mode;
  bool isGsArmed = static_cast<unsigned long long>(autopilotStateMachineOutput.vertical_mode_armed) >> 4 & 0x01;
  bool isGsEngaged = autopilotStateMachineOutput.vertical_mode >= 30 && autopilotStateMachineOutput.vertical_mode <= 34;
  bool isLandOrGAModeActive = ((isLocArmed || isLocEngaged) && (isGsArmed || isGsEngaged)) || (activeLatMode == 50 && activeVertMode == 41);
  bool pulsedFcuCommand = apFcuCommandPulseNode.update(discreteInputs.apFcuCommand);

  // TODO add flight condition
  bool flightCondition = true;  // apEngagedGroundConditionConfirmNode.update(false, deltaTime) && raBus.radioHeight.value() > 100;
  // TODO add FAC condition
  bool apCondition = !discreteInputs.apInstDisc && !discreteInputs.elacOwnApDisc && !discreteInputs.elacOppApDisc;

  bool softDisengageCondition =
      !apFdAthrCommonCondition || !apFdCommonCondition || !apCondition || (isApEngaged && pulsedFcuCommand) ||
      (apEngagedOppConditionConfirmNode.update(isApEngaged, deltaTime) && discreteInputs.apOppEngaged && !isLandOrGAModeActive) ||
      (isApEngaged && discreteInputs.apOppEngaged && apEngagedLandGaConditionPulseNode.update(isLandOrGAModeActive) && !side1);

  bool softEngageCondition = apFdAthrCommonCondition && apFdCommonCondition && apCondition && flightCondition && pulsedFcuCommand;

  bool apEngagedSoft = apEngagedFlipFlopSoftware.update(softEngageCondition, softDisengageCondition);

  bool hardwareDisengageCondition = discreteInputs.apInstDisc || !apEngagedConfirmNode.update(apEngagedSoft, deltaTime);
  bool hardwareEngageCondition = pulsedFcuCommand && apEngagedSoft;

  isApEngaged = apEngagedFlipFlopHardware.update(hardwareEngageCondition, hardwareDisengageCondition);
  isApInop = !apFdAthrCommonCondition || !apFdCommonCondition || !apCondition;
}

void Fmgc::computeAthrEngagement(double deltaTime) {
  bool athrDisabled = athrDisableFlipFlip.update(athrDisableConfirmNode.update(discreteInputs.athrInstDisc, deltaTime), false);

  // TODO add ATHR condition
  bool athrCondition = !athrDisabled;

  auto activeLatMode = autopilotStateMachineOutput.lateral_mode;
  auto activeVertMode = autopilotStateMachineOutput.vertical_mode;
  bool isLandTrackModeActive = activeLatMode >= 32 && activeLatMode <= 34 && activeVertMode >= 32 && activeVertMode <= 34;

  bool athrEngageCondition =
      apFdAthrCommonCondition && athrCondition &&
      (discreteInputs.athrFcuCommand && (raBus.radioHeight.value() > 100) || (alphaFloorCondition && raBus.radioHeight.value() > 100) ||
       autopilotStateMachineOutput.vertical_mode == 40 || autopilotStateMachineOutput.vertical_mode == 41);

  bool athrDisengageCondition = !(apFdAthrCommonCondition && athrCondition) || discreteInputs.athrInstDisc ||
                                (isAthrEngaged && discreteInputs.athrFcuCommand && !isLandTrackModeActive);

  isAthrEngaged = athrEngagedFlipFlop.update(athrEngageCondition, athrDisengageCondition);
  isAthrInop = !apFdAthrCommonCondition || !athrCondition;
}

void Fmgc::computeLandingCapability() {
  const auto ownActiveVertMode = autopilotStateMachineOutput.vertical_mode;
  const auto ownActiveLatMode = autopilotStateMachineOutput.lateral_mode;
  const auto ownArmedVertMode = static_cast<int>(autopilotStateMachineOutput.vertical_mode_armed);
  const auto ownArmedLatMode = static_cast<int>(autopilotStateMachineOutput.lateral_mode_armed);

  const bool ownLandModeArmedEngaged =
      ((ownArmedLatMode >> 1) & 1 || ownActiveLatMode == lateral_mode_LOC_CPT || ownActiveLatMode == lateral_mode_LOC_TRACK) &&
      ((ownArmedVertMode >> 4 & 1) || ownActiveVertMode == vertical_mode_GS_CPT || ownActiveVertMode == vertical_mode_GS_TRACK);

  const auto oppLandModeArmedEngaged =
      busInputs.fmgcOpp.discreteWord3.bitFromValueOr(20, false) || busInputs.fmgcOpp.discreteWord4.bitFromValueOr(14, false);

  const bool ownApEngagedInLandMode = isApEngaged && ownLandModeArmedEngaged;
  const bool oppApEngagedInLandMode = discreteInputs.apOppEngaged && oppLandModeArmedEngaged;

  const bool landing2Condition = (discreteInputs.fwcOwnValid || discreteInputs.fwcOppValid) && discreteInputs.pfdOwnValid &&
                                 discreteInputs.pfdOppValid && !ilsOwnInvalid && !ilsOwnInvalid;

  const bool landing3PassiveCondition = landing2Condition && !raOwnInvalid && !raOppInvalid;

  const bool anyIrFailed = irOwnInvalid || irOppInvalid || ir3Invalid;
  const bool anyAdrFailed = adrOwnInvalid || adrOppInvalid || adr3Invalid;
  const bool landing3OperationalCondition =
      discreteInputs.fwcOwnValid && discreteInputs.fwcOppValid && discreteInputs.powerSupplySplit && discreteInputs.pfdOwnValid &&
      discreteInputs.pfdOppValid && !ilsOwnInvalid && !ilsOppInvalid && !raOwnInvalid && !raOppInvalid && !anyIrFailed && !anyAdrFailed &&
      discreteInputs.bscuOwnValid && discreteInputs.bscuOppValid && discreteInputs.facOwnHealthy && discreteInputs.facOppHealthy;

  land3OperationalCapacity =
      landing3OperationalCondition && (isAthrEngaged || discreteInputs.athrOppEngaged) && ownApEngagedInLandMode && oppApEngagedInLandMode;
  land3PassiveCapacity = !land3OperationalCapacity && landing2Condition && landing3PassiveCondition &&
                         (isAthrEngaged || discreteInputs.athrOppEngaged) && (ownApEngagedInLandMode || oppApEngagedInLandMode);
  land2Capacity =
      !land3OperationalCapacity && !land3PassiveCapacity && landing2Condition && (ownApEngagedInLandMode || oppApEngagedInLandMode);

  land2Inop = !landing2Condition || (isApInop && busInputs.fmgcOpp.discreteWord4.bitFromValueOr(19, true));
  land3PassiveInop = !landing3PassiveCondition || land2Inop || (isAthrInop && busInputs.fmgcOpp.discreteWordAthr.bitFromValueOr(24, true));
  land3OperationalInop = !landing3OperationalCondition || isApInop || busInputs.fmgcOpp.discreteWord4.bitFromValueOr(19, true) ||
                         (isAthrInop && busInputs.fmgcOpp.discreteWordAthr.bitFromValueOr(24, true));
}

FmgcDiscreteOutputs Fmgc::getDiscreteOutputs() {
  discreteOutputs.fcuFail = false;
  discreteOutputs.fmgcHealthy = true;
  discreteOutputs.ilsTestInhibit = false;
  discreteOutputs.stickLock = isApEngaged;
  discreteOutputs.fdOwnEngaged = isFdEngaged;
  discreteOutputs.apOwnEngaged = isApEngaged;
  discreteOutputs.athrOwnEngaged = isAthrEngaged;

  return discreteOutputs;
}

FmgcABus Fmgc::getBusOutputs() {
  const auto activeVertMode = autopilotStateMachineOutput.vertical_mode;
  const auto activeLatMode = autopilotStateMachineOutput.lateral_mode;
  const auto armedVertMode = static_cast<int>(autopilotStateMachineOutput.vertical_mode_armed);
  const auto armedLatMode = static_cast<int>(autopilotStateMachineOutput.lateral_mode_armed);
  const bool trkFpaModeActive = busInputs.fcuOwn.fcuDiscreteWord1.bitFromValue(25);

  // Set Discrete word 1
  busOutputs.discreteWord1.setSsm(NormalOperation);
  busOutputs.discreteWord1.setBit(
      11, activeVertMode == vertical_mode::vertical_mode_CLB || activeVertMode == vertical_mode::vertical_mode_OP_CLB);
  busOutputs.discreteWord1.setBit(
      12, activeVertMode == vertical_mode::vertical_mode_DES || activeVertMode == vertical_mode::vertical_mode_OP_DES);
  busOutputs.discreteWord1.setBit(13, false);
  busOutputs.discreteWord1.setBit(
      14, activeVertMode == vertical_mode::vertical_mode_OP_DES || activeVertMode == vertical_mode::vertical_mode_OP_CLB);
  busOutputs.discreteWord1.setBit(15, activeVertMode == vertical_mode::vertical_mode_SRS);
  busOutputs.discreteWord1.setBit(16, activeVertMode == vertical_mode::vertical_mode_SRS_GA);
  busOutputs.discreteWord1.setBit(17, activeVertMode == vertical_mode::vertical_mode_VS && !trkFpaModeActive);
  busOutputs.discreteWord1.setBit(18, activeVertMode == vertical_mode::vertical_mode_VS && trkFpaModeActive);
  busOutputs.discreteWord1.setBit(
      19, activeVertMode == vertical_mode::vertical_mode_ALT || activeVertMode == vertical_mode::vertical_mode_ALT_CPT ||
              activeVertMode == vertical_mode::vertical_mode_ALT_CST || activeVertMode == vertical_mode::vertical_mode_ALT_CST_CPT);
  busOutputs.discreteWord1.setBit(20, activeVertMode == vertical_mode::vertical_mode_ALT ||
                                          activeVertMode == vertical_mode::vertical_mode_ALT_CST ||
                                          activeVertMode == vertical_mode::vertical_mode_GS_TRACK);
  busOutputs.discreteWord1.setBit(21, activeVertMode == vertical_mode::vertical_mode_ALT_CPT ||
                                          activeVertMode == vertical_mode::vertical_mode_ALT_CST_CPT ||
                                          activeVertMode == vertical_mode::vertical_mode_GS_CPT);
  busOutputs.discreteWord1.setBit(
      22, activeVertMode == vertical_mode::vertical_mode_GS_TRACK || activeVertMode == vertical_mode::vertical_mode_GS_CPT);
  busOutputs.discreteWord1.setBit(23, activeVertMode == vertical_mode::vertical_mode_FINAL_DES);
  busOutputs.discreteWord1.setBit(24, autopilotStateMachineOutput.EXPED_mode_active);
  busOutputs.discreteWord1.setBit(25, activeVertMode == vertical_mode_FLARE);
  busOutputs.discreteWord1.setBit(26, autopilotStateMachineOutput.ALT_soft_mode_active);
  busOutputs.discreteWord1.setBit(27, false);

  // Set discrete Word 2
  busOutputs.discreteWord2.setSsm(NormalOperation);
  busOutputs.discreteWord2.setBit(11,
                                  activeLatMode == lateral_mode::lateral_mode_RWY || activeLatMode == lateral_mode::lateral_mode_RWY_TRACK);
  busOutputs.discreteWord2.setBit(12, activeLatMode == lateral_mode::lateral_mode_NAV);
  busOutputs.discreteWord2.setBit(13, activeLatMode == lateral_mode::lateral_mode_LOC_CPT);
  busOutputs.discreteWord2.setBit(14, activeLatMode == lateral_mode::lateral_mode_LOC_TRACK);
  busOutputs.discreteWord2.setBit(15, activeLatMode == lateral_mode::lateral_mode_GA_TRACK);
  busOutputs.discreteWord2.setBit(16, activeLatMode == lateral_mode::lateral_mode_HDG && !trkFpaModeActive);
  busOutputs.discreteWord2.setBit(17, activeLatMode == lateral_mode::lateral_mode_HDG && trkFpaModeActive);
  busOutputs.discreteWord2.setBit(20, activeLatMode == lateral_mode::lateral_mode_RWY);
  busOutputs.discreteWord2.setBit(21, false);
  busOutputs.discreteWord2.setBit(22, false);
  busOutputs.discreteWord2.setBit(23, activeLatMode == lateral_mode::lateral_mode_RWY_TRACK);
  busOutputs.discreteWord2.setBit(24, false);
  busOutputs.discreteWord2.setBit(25, false);
  busOutputs.discreteWord2.setBit(26, activeLatMode == lateral_mode::lateral_mode_ROLL_OUT);
  busOutputs.discreteWord2.setBit(28, false);

  // Set discrete Word 3
  busOutputs.discreteWord3.setSsm(NormalOperation);
  busOutputs.discreteWord3.setBit(11, false);
  busOutputs.discreteWord3.setBit(12, (armedVertMode >> 0) & 1 || (armedVertMode >> 1) & 1);
  busOutputs.discreteWord3.setBit(13, false);
  busOutputs.discreteWord3.setBit(14, (armedLatMode >> 0) & 1);
  busOutputs.discreteWord3.setBit(15, false);
  busOutputs.discreteWord3.setBit(16, (armedLatMode >> 1) & 1);
  busOutputs.discreteWord3.setBit(17, false);
  busOutputs.discreteWord3.setBit(18, false);
  busOutputs.discreteWord3.setBit(19, false);
  busOutputs.discreteWord3.setBit(
      20, ((armedLatMode >> 1) & 1 || activeLatMode == lateral_mode_LOC_CPT || activeLatMode == lateral_mode_LOC_TRACK) &&
              ((armedVertMode >> 4 & 1) || activeVertMode == vertical_mode_GS_CPT || activeVertMode == vertical_mode_GS_TRACK));
  busOutputs.discreteWord3.setBit(21, false);
  busOutputs.discreteWord3.setBit(22, (armedVertMode >> 4 & 1));
  busOutputs.discreteWord3.setBit(23, (armedVertMode >> 5 & 1));
  busOutputs.discreteWord3.setBit(24, (armedVertMode >> 2 & 1));
  busOutputs.discreteWord3.setBit(25, (armedVertMode >> 3 & 1));
  busOutputs.discreteWord3.setBit(26, false);
  busOutputs.discreteWord3.setBit(27, false);
  busOutputs.discreteWord3.setBit(28, false);
  busOutputs.discreteWord3.setBit(29, false);

  // Set Discrete Word 4
  busOutputs.discreteWord4.setSsm(NormalOperation);
  busOutputs.discreteWord4.setBit(11, discreteInputs.apInstDisc);
  busOutputs.discreteWord4.setBit(12, isApEngaged);
  busOutputs.discreteWord4.setBit(13, isFdEngaged);
  busOutputs.discreteWord4.setBit(14, activeVertMode >= lateral_mode_LAND && activeLatMode <= lateral_mode_ROLL_OUT);
  busOutputs.discreteWord4.setBit(19, isApInop);
  busOutputs.discreteWord4.setBit(20, land2Inop);
  busOutputs.discreteWord4.setBit(21, land3PassiveInop);
  busOutputs.discreteWord4.setBit(22, land3OperationalInop);
  busOutputs.discreteWord4.setBit(23, land2Capacity);
  busOutputs.discreteWord4.setBit(24, land3PassiveCapacity);
  busOutputs.discreteWord4.setBit(25, land3OperationalCapacity);

  // Set Discrete Word 5
  busOutputs.discreteWord5.setSsm(NormalOperation);
  busOutputs.discreteWord5.setBit(11, false);
  busOutputs.discreteWord5.setBit(12, false);
  busOutputs.discreteWord5.setBit(13, false);
  busOutputs.discreteWord5.setBit(14, false);
  busOutputs.discreteWord5.setBit(15, false);
  busOutputs.discreteWord5.setBit(16, false);
  busOutputs.discreteWord5.setBit(17, false);
  busOutputs.discreteWord5.setBit(19, false);
  busOutputs.discreteWord5.setBit(20, true);
  busOutputs.discreteWord5.setBit(24, false);
  busOutputs.discreteWord5.setBit(27, false);
  busOutputs.discreteWord5.setBit(28, false);
  busOutputs.discreteWord5.setBit(29, false);

  // Set Discrete Word 7
  busOutputs.discreteWord7.setSsm(NormalOperation);
  busOutputs.discreteWord7.setBit(11, true);  // AP/FD TCAS mode installed
  busOutputs.discreteWord7.setBit(12, (armedVertMode >> 6 & 1));
  busOutputs.discreteWord7.setBit(13, activeVertMode == vertical_mode_TCAS);

  // Set Discrete Word ATHR
  busOutputs.discreteWordAthr.setSsm(NormalOperation);
  busOutputs.discreteWordAthr.setBit(13, isAthrEngaged);
  busOutputs.discreteWordAthr.setBit(14, false);
  busOutputs.discreteWordAthr.setBit(17, discreteInputs.athrInstDisc);
  busOutputs.discreteWordAthr.setBit(18, false);
  busOutputs.discreteWordAthr.setBit(19, false);
  busOutputs.discreteWordAthr.setBit(20, false);
  busOutputs.discreteWordAthr.setBit(24, isAthrInop);

  // Set Discrete Word ATHR FMA
  busOutputs.discreteWordAthrFma.setSsm(NormalOperation);
  busOutputs.discreteWordAthrFma.setBit(13, isAthrEngaged);
  busOutputs.discreteWordAthrFma.setBit(14, false);
  busOutputs.discreteWordAthrFma.setBit(17, discreteInputs.athrInstDisc);
  busOutputs.discreteWordAthrFma.setBit(18, false);
  busOutputs.discreteWordAthrFma.setBit(19, false);
  busOutputs.discreteWordAthrFma.setBit(20, false);

  // Set numeric outputs
  const bool showLateralFd =
      activeLatMode != lateral_mode_NONE && activeLatMode != lateral_mode_ROLL_OUT && activeLatMode != lateral_mode_RWY;
  busOutputs.rollFdCommand.setFromData(-autopilotLawsOutput.flight_director.Phi_c_deg,
                                       showLateralFd && isFdEngaged ? NormalOperation : NoComputedData);

  const bool showVerticalFd = activeVertMode != vertical_mode_NONE && activeVertMode != vertical_mode_ROLL_OUT;
  busOutputs.pitchFdCommand.setFromData(-autopilotLawsOutput.flight_director.Theta_c_deg,
                                        showVerticalFd && isFdEngaged ? NormalOperation : NoComputedData);

  const bool showYawFd =
      activeLatMode == lateral_mode_RWY || activeLatMode == lateral_mode_ROLL_OUT || activeVertMode == vertical_mode_FLARE;
  busOutputs.yawFdCommand.setFromData(autopilotLawsOutput.flight_director.Beta_c_deg,
                                      showYawFd && isFdEngaged ? NormalOperation : NoComputedData);

  return busOutputs;
}

void Fmgc::updateApSm(bool autopilotStateMachineEnabled, double deltaTime, double simulationTime) {}

bool Fmgc::anyAdrBusWordInvalid(AirDataBus bus) {
  return !(bus.altitudeStandard.isNo() || bus.altitudeCorrected.isNo() || bus.mach.isNo() || bus.airspeedComputed.isNo() ||
           bus.airspeedTrue.isNo() || bus.aoaCorrected.isNo() || bus.verticalSpeed.isNo());
}

bool Fmgc::anyIrBusWordInvalid(InertialReferenceBus bus) {
  return !bus.bodyLatAccel.isNo();
}
