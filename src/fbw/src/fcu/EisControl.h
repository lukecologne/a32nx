#pragma once

#include "../Arinc429.h"
#include "FcuDiscretes.h"
#include "SimConnectData.h"

enum class EfisFilterSelection { NONE, CSTR, WPT, VORD, NDB, ARPT };

const int minHPAValue = 745;
const int maxHPAValue = 1050;
const float minInHgValue = 21.99;
const float maxInHgValue = 31.00;

const float inHg2hPa = 33.8639;
const float hPa2InHg = 0.02953;

class EisControlPanel {
 public:
  bool baroIsStd;

  bool baroIsQfe;

  float baroInHgValue;

  int barohPaValue;

  bool fdActive;

  bool lsActive;

  Arinc429DiscreteWord outWord1 = {};

  Arinc429DiscreteWord outWord2 = {};

  EfisFilterSelection selectedFilter;

  SimInputFcuEis inputEvents;

  EfisDiscreteInputs discreteInputs;

  EisControlPanel();

  void init();

  void step();

  Arinc429DiscreteWord getEisWord1();

  Arinc429DiscreteWord getEisWord2();
};
