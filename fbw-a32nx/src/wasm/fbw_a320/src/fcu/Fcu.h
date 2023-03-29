#pragma once

#include "../model/FmgcComputer_types.h"
#include "FcuIO.h"

class Fcu {
 public:
  Fcu();

  void update(double deltaTime, double simulationTime, bool fcu1FaultActive, bool fcu2FaultActive, bool fcu1IsPowered, bool fcu2IsPowered);

  base_fcu_bus getBusOutputs();

  FcuFrontPanelOutputs getFrontPanelOutputs();

  FcuBusInputs busInputs;

  FcuDiscreteInputs discreteInputs;

  FcuFrontPanelInputs frontPanelInputs;

 private:
  void initSelfTests();

  void clearMemory();

  void monitorPowerSupply(double deltaTime, bool isPowered);

  void monitorSelf(bool faultActive);

  void updateSelfTest(double deltaTime);

  // Computer Self-monitoring vars
  bool facHealthy;

  // Power Supply monitoring
  double powerSupplyOutageTime;

  bool longPowerFailure;

  bool shortPowerFailure;

  // Selftest vars
  double selfTestTimer;

  bool selfTestComplete;

  // Constants
  const double longPowerFailureTime = 0.2;
  const double shortPowerFailureTime = 0.01;
  const double selfTestDuration = 10;
};
