#include "Fcu.h"
#include "../Arinc429Utils.h"

Fcu::Fcu() {}

void Fcu::update(double deltaTime,
                 double simulationTime,
                 bool fcu1FaultActive,
                 bool fcu2FaultActive,
                 bool fcu1IsPowered,
                 bool fcu2IsPowered) {}

base_fcu_bus Fcu::getBusOutputs() {
  base_fcu_bus output = {};

  return output;
}

FcuFrontPanelOutputs Fcu::getFrontPanelOutputs() {
  FcuFrontPanelOutputs output = {};

  return output;
}
