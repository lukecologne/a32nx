#pragma once

#include "../busStructures/busStructures.h"
#include "../model/AutopilotLaws.h"
#include "../model/AutopilotStateMachine.h"
#include "../model/Autothrust.h"
#include "../utils/ConfirmNode.h"
#include "../utils/PulseNode.h"
#include "../utils/SRFlipFlop.h"
#include "fmgcBusses.h"
#include "fmgcDiscretes.h"

#include "../Arinc429.h"

class Fmgc {
 public:
  Fmgc(bool isSide1);

  /*
   * In this function, all the internal state of the FMGC is initialized.
   * This function is called either after construction, or after a power loss that lastet for more than
   * 200ms.
   */
  void init();

  void step(double deltaTime, double simulationTime, bool isPowered);

  FmgcDiscreteOutputs getDiscreteOutputs();

  FmgcABus getBusOutputs();

  FmgcDiscreteInputs discreteInputs;

  FmgcBusInputs busInputs;

  // These are public for now, until they are running independantly in the FMGCs. Currently, they are running
  // outside, and only their outputs are sent to the FMGCs.
  // Model Data
  // AutopilotLawsModelClass autopilotLaws;
  // AutopilotLawsModelClass::ExternalInputs_AutopilotLaws_T autopilotLawsInput = {};
  ap_raw_output autopilotLawsOutput;

  // AutopilotStateMachineModelClass stateMachine;
  // AutopilotStateMachineModelClass::ExternalInputs_AutopilotStateMachine_T autopilotStateMachineInput = {};
  ap_raw_laws_input autopilotStateMachineOutput;

  // AutothrustModelClass autoThrust;
  // AutothrustModelClass::ExternalInputs_Autothrust_T autoThrustInput = {};
  athr_output autoThrustOutput;

 private:
  void monitorAdirsValidity();

  void monitorRaValidity();

  void monitorFacValidity();

  void monitorIlsValidity();

  void computeApFdAthrConditions();

  void computeFdEngagement(double deltaTime);

  void computeApEngagement(double deltaTime);

  void computeAthrEngagement(double deltaTime);

  void computeLandingCapability();

  void updateApSm(bool autopilotStateMachineEnabled, double deltaTime, double simulationTime);

  void updateApLaws(bool autopilotLawsEnabled, double deltaTime, double simulationTime);

  void writeOutputs();

  bool anyAdrBusWordInvalid(AirDataBus bus);

  bool anyIrBusWordInvalid(InertialReferenceBus bus);

  const bool side1;

  // ADIRS monitoring
  bool adrOwnInvalid;

  bool adrOppInvalid;

  bool adr3Invalid;

  bool dualAdrFailure;

  bool irOwnInvalid;

  bool irOppInvalid;

  bool ir3Invalid;

  bool dualIrFailure;

  // RA monitioring
  bool raOwnInvalid;

  bool raOppInvalid;

  // FAC monitoring
  bool facOwnInvalid;

  bool facOppInvalid;

  // ILS monitoring

  bool ilsOwnInvalid;

  bool ilsOppInvalid;

  // AP/FD/ATHR conditions;
  bool apFdAthrCommonCondition;

  bool apFdCommonCondition;

  // FD vars
  bool isFdEngaged;

  // AP vars
  bool isApEngaged;

  bool isApInop;

  // ATHR vars
  bool isAthrEngaged;

  bool isAthrInop;

  bool alphaFloorCondition;

  // Landing capability vars

  bool land2Capacity;

  bool land3PassiveCapacity;

  bool land3OperationalCapacity;

  bool land2Inop;

  bool land3PassiveInop;

  bool land3OperationalInop;

  // FlipFlops
  SRFlipFlop apEngagedFlipFlopSoftware = SRFlipFlop(false);

  SRFlipFlop apEngagedFlipFlopHardware = SRFlipFlop(false);

  SRFlipFlop athrEngagedFlipFlop = SRFlipFlop(false);

  SRFlipFlop athrDisableFlipFlip = SRFlipFlop(false);

  // Confirm Nodes
  ConfirmNode fdEngagedConfirmNode = ConfirmNode(false, 0.2);

  ConfirmNode apEngagedConfirmNode = ConfirmNode(false, 0.2);

  ConfirmNode apEngagedGroundConditionConfirmNode = ConfirmNode(true, 5);

  ConfirmNode apEngagedOppConditionConfirmNode = ConfirmNode(true, 0.2);

  ConfirmNode athrDisableConfirmNode = ConfirmNode(true, 15);

  // Pulse Nodes
  PulseNode apEngagedLandGaConditionPulseNode = PulseNode(false);

  PulseNode apFcuCommandPulseNode = PulseNode(true);

  // Busses that are used for computations
  AirDataBus adrBus;

  InertialReferenceBus irBus;

  RaBus raBus;

  FacBus facBus;

  FcdcBus fcdcBus;

  IlsBus ilsBus;

  DmeBus dmeBus;

  // Bus and discrete In-/Outputs
  FmgcDiscreteOutputs discreteOutputs;

  FmgcABus busOutputs;
};
