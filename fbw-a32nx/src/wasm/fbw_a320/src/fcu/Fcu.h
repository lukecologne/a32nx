#pragma once
#include "../model/FcuComputer.h"

class Fcu {
 public:
  Fcu();

  void update(double deltaTime, double simulationTime, bool fcu1FaultActive, bool fcu2FaultActive, bool fcu1IsPowered, bool fcu2IsPowered);

  base_fcu_bus getBusOutputs();

  base_fcu_discrete_outputs getDiscreteOutputs();

  FcuComputer::ExternalInputs_FcuComputer_T modelInputs = {};

 private:
  // Model
  FcuComputer fcuComputer;
  fcu_outputs modelOutputs;

  // Computer Self-monitoring vars
  bool fcuHealthy;

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
