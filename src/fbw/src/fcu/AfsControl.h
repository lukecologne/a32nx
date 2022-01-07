#pragma once

#include "../Arinc429.h"
#include "../busStructures/busStructures.h"
#include "../interface/SimConnectData.h"
#include "../utils/ConfirmNode.h"
#include "FcuDiscretes.h"

const float minMachValue = 0.1;
const float maxMachValue = 0.99;
const float minSpeedValue = 100;
const float maxSpeedValue = 399;
const float spdMachTimeout = 10;
const float hdgTrkTimeout = 45;
const int minAltValue = 100;
const int maxAltValue = 49000;
const float minVsValue = -6000;
const float maxVsValue = 6000;
const float minFpaValue = -9.9;
const float maxFpaValue = 9.9;
const float vsFpaTimeout = 45;

class AfsControlPanel {
 public:
  float speedMachDisplayValue;

  bool speedMachInDisplay;

  ConfirmNode speedMachTimer = ConfirmNode(true, spdMachTimeout);

  bool headingTrackInDisplay;

  int headingTrackValue;

  ConfirmNode headingTrackTimer = ConfirmNode(true, hdgTrkTimeout);

  int altitudeDisplayValue;

  float vsFpaValue;

  bool vsFpaInDisplay;

  ConfirmNode vsFpaTimer = ConfirmNode(true, hdgTrkTimeout);

  bool trkFpaActive;

  bool altInMeters;

  Arinc429DiscreteWord outWord1 = {};

  Arinc429DiscreteWord outWord2 = {};

  AfsControlPanel();

  void init();

  void step(double deltaTime, FmgcABus fmgcBus);

  SimInputFcuAfs inputEvents;

  AfsDiscreteInputs afsDiscreteInputs;

  Arinc429DiscreteWord getFcuWord1();

  Arinc429DiscreteWord getFcuWord2();

 private:
  void handleSpeedControl(double deltaTime, FmgcABus fmgcBus);

  void handleLateralControl(double deltaTime, FmgcABus fmgcBus);

  void handleAltValue();

  void handleVerticalControl(double deltaTime, FmgcABus fmgcBus);
};
