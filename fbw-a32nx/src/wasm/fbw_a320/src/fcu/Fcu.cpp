#include "Fcu.h"
#include "../Arinc429Utils.h"

Fcu::Fcu() {
  fcuComputer.initialize();
}

void Fcu::update(double deltaTime,
                 double simulationTime,
                 bool fcu1FaultActive,
                 bool fcu2FaultActive,
                 bool fcu1IsPowered,
                 bool fcu2IsPowered) {
  modelInputs.in.sim_data.computer_running = true;
  fcuHealthy = true;

  fcuComputer.setExternalInputs(&modelInputs);
  fcuComputer.step();
  modelOutputs = fcuComputer.getExternalOutputs().out;
}

base_fcu_bus Fcu::getBusOutputs() {
  if (!fcuHealthy) {
    return {};
  }

  return modelOutputs.bus_outputs;
}

base_fcu_discrete_outputs Fcu::getDiscreteOutputs() {
  base_fcu_discrete_outputs output = {};

  output.fcu_healthy = fcuHealthy;
  if (!fcuHealthy) {
    return output;
  } else {
    return modelOutputs.discrete_outputs;
  }
}
