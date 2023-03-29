#pragma once

#include "../model/FmgcComputer_types.h"

struct FcuDiscreteInputs {
  bool ap1Engaged;
  bool fd1Engaged;
  bool athr1Engaged;

  bool ap2Engaged;
  bool fd2Engaged;
  bool athr2Engaged;

  bool lightsTest;
};

struct FcuBusInputs {
  base_fmgc_a_bus fmgc1BusInputs;

  base_fmgc_a_bus fmgc2BusInputs;
};

enum class EfisModeSelection { ROSE_ILS, ROSE_VOR, ROSE_NAV, ARC, PLAN };

enum class EfisRangeSelection { RANGE10, RANGE20, RANGE40, RANGE80, RANGE160, RANGE320 };

enum class NavaidSelection { VOR, ADF, NONE };

struct FcuEfisPanelInputs {
  EfisRangeSelection efisRange;

  EfisModeSelection efisMode;

  NavaidSelection navaid1Mode;

  NavaidSelection navaid2Mode;

  bool baroIsInhg;

  bool baroKnobPushed;

  bool baroKnobPulled;

  int baroKnobTurns;

  bool fdButtonPushed;

  bool lsButtonPushed;

  bool cstrButtonPushed;

  bool wptButtonPushed;

  bool vordButtonPushed;

  bool ndbButtonPushed;

  bool arptButtonPushed;
};

struct FcuFrontPanelInputs {
  FcuEfisPanelInputs efisDiscreteIn[2];

  bool locButtonPressed;

  bool expedButtonPressed;

  bool apprButtonPressed;

  bool spdMachButtonPressed;

  bool trkFpaButtonPressed;

  bool metricAltButtonPressed;

  bool speedKnobPushed;

  bool speedKnobPulled;

  int speedKnobTurns;

  bool hdgTrkKnobPushed;

  bool hdgTrkKnobPulled;

  int hdgTrkKnobTurns;

  bool altKnobPushed;

  bool altKnobPulled;

  int altKnobTurns;

  bool altIncrement1000;

  bool vsKnobPushed;

  bool vsKnobPulled;

  int vsKnobTurns;
};

struct FcuEfisPanelOutputs {
  bool fdLightOn;

  bool lsLightOn;

  bool cstrLightOn;

  bool wptLightOn;

  bool vorDLightOn;

  bool ndbLightOn;

  bool arptLightOn;
};

struct FcuFrontPanelOutputs {
  FcuEfisPanelOutputs efisDiscreteOut[2];

  bool locLightOn;

  bool expedLightOn;

  bool apprLightOn;

  bool ap1LightOn;

  bool ap2LightOn;

  bool athrLightOn;
};
