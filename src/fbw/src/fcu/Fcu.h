#pragma once

#include "../Arinc429.h"
#include "../busStructures/busStructures.h"
#include "AfsControl.h"
#include "EisControl.h"
#include "FcuDiscretes.h"
#include "SimConnectData.h"

class Fcu {
 public:
  Fcu();

  void init();

  void step(double deltaTime, bool dcBus2Active, bool dcEssBusActive);

  FcuBus getBusOutput();

  FcuDiscreteOutputs getDiscreteOutputs();

  FmgcABus fmgc1BusInput;

  FmgcABus fmgc2BusInput;

  FcuDiscreteInputs discreteInputs;

  SimInputFcu inputEvents;

 private:
  void computeFmgcPriority();

  void writeOutputs();

  bool fmgc1HasPriority;

  AfsControlPanel afsControl;

  EisControlPanel eisControl[2];

  FcuBus fcuBusOutput;

  FcuDiscreteOutputs fcuDiscreteOutputs;
};
