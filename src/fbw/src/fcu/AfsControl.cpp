#include "AfsControl.h"
#include <algorithm>
#include <cmath>

#undef max
#undef min

AfsControlPanel::AfsControlPanel() {}

void AfsControlPanel::init() {
  speedMachDisplayValue = 0;
  headingTrackValue = 0;
  altitudeDisplayValue = 0;
  vsFpaValue = 0;

  trkFpaActive = false;
  altInMeters = false;

  speedMachTimer.update(false, 0);
  headingTrackTimer.update(false, 0);
  vsFpaTimer.update(false, 0);
}

void AfsControlPanel::step(double deltaTime, FmgcABus fmgcBus) {
  if (inputEvents.TRK_FPA_push) {
    trkFpaActive = !trkFpaActive;
  }

  if (inputEvents.METRIC_ALT_push) {
    altInMeters = !altInMeters;
  }

  // Handle Speed control
  const bool isSpeedAutoControlActive = fmgcBus.discreteWord5.bitFromValue(19);
  const bool isMachActive = fmgcBus.discreteWord5.bitFromValue(0);

  handleSpeedControl(deltaTime, fmgcBus);
  handleLateralControl(deltaTime, fmgcBus);
  handleAltValue();
  handleVerticalControl(deltaTime, fmgcBus);
}

void AfsControlPanel::handleSpeedControl(double deltaTime, FmgcABus fmgcBus) {
  const bool isSpeedSelected = fmgcBus.discreteWord5.bitFromValue(20);
  const bool machModeActive = fmgcBus.discreteWordAthr.bitFromValue(19);

  if (!speedMachInDisplay && isSpeedSelected) {
    speedMachDisplayValue = machModeActive ? std::max(std::min(std::roundf(fmgcBus.mach.value() * 100) / 100, minMachValue), maxMachValue)
                                           : std::max(std::min(std::roundf(fmgcBus.cas.value()), maxSpeedValue), minSpeedValue);
    speedMachInDisplay = true;
  }

  if (!machModeActive) {
    if (speedMachInDisplay && inputEvents.SPEED_MACH_dec) {
      speedMachDisplayValue = std::max(std::min(std::roundf(speedMachDisplayValue - 1), maxSpeedValue), minSpeedValue);
    } else if (speedMachInDisplay && inputEvents.SPEED_MACH_inc) {
      speedMachDisplayValue = std::max(std::min(std::roundf(speedMachDisplayValue + 1), maxSpeedValue), minSpeedValue);
    } else if (!speedMachInDisplay && (inputEvents.SPEED_MACH_inc || inputEvents.SPEED_MACH_dec)) {
      speedMachDisplayValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
      speedMachInDisplay = true;
    }
  } else {
    if (speedMachInDisplay && inputEvents.SPEED_MACH_dec) {
      speedMachDisplayValue = std::max(std::min(std::roundf((speedMachDisplayValue - 0.01) * 100) / 100, maxMachValue), minMachValue);
    } else if (speedMachInDisplay && inputEvents.SPEED_MACH_inc) {
      speedMachDisplayValue = std::max(std::min(std::roundf((speedMachDisplayValue + 0.01) * 100) / 100, minMachValue), maxMachValue);
    } else if (!speedMachInDisplay && (inputEvents.SPEED_MACH_inc || inputEvents.SPEED_MACH_dec)) {
      speedMachDisplayValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
      speedMachInDisplay = true;
    }
  }

  if (!isSpeedSelected && (inputEvents.SPEED_MACH_inc || inputEvents.SPEED_MACH_dec)) {
    speedMachTimer.update(false, deltaTime);
  }

  if (speedMachInDisplay && !isSpeedSelected) {
    speedMachTimer.update(true, deltaTime);
  } else if (isSpeedSelected) {
    speedMachTimer.update(false, deltaTime);
  }

  if (speedMachTimer.getOutput() && speedMachInDisplay && !isSpeedSelected) {
    speedMachDisplayValue = 0;
    speedMachInDisplay = false;
  }
}

void AfsControlPanel::handleLateralControl(double deltaTime, FmgcABus fmgcBus) {
  const bool isLateralSelectedModeActive = fmgcBus.discreteWord2.bitFromValue(16) || fmgcBus.discreteWord2.bitFromValue(17);
  const bool isHeadingPresetAvailable = fmgcBus.discreteWord3.bitFromValue(11);

  if (!headingTrackInDisplay && isLateralSelectedModeActive) {
    headingTrackValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
    headingTrackInDisplay = true;
  }

  if (headingTrackInDisplay && inputEvents.HDG_TRK_dec) {
    headingTrackValue = (headingTrackValue - 1 + 360) % 360;
  } else if (headingTrackInDisplay && inputEvents.HDG_TRK_inc) {
    headingTrackValue = (headingTrackValue + 1 + 360) % 360;
  } else if (!headingTrackInDisplay && (inputEvents.HDG_TRK_inc || inputEvents.HDG_TRK_dec)) {
    headingTrackValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
    headingTrackInDisplay = true;
  }

  if (!isLateralSelectedModeActive && (inputEvents.HDG_TRK_inc || inputEvents.HDG_TRK_dec)) {
    headingTrackTimer.update(false, deltaTime);
  }

  if (headingTrackInDisplay && !isLateralSelectedModeActive) {
    headingTrackTimer.update(true, deltaTime);
  } else if (isLateralSelectedModeActive) {
    headingTrackTimer.update(false, deltaTime);
  }

  if (headingTrackTimer.getOutput() && headingTrackInDisplay && !isLateralSelectedModeActive) {
    headingTrackValue = 0;
    headingTrackInDisplay = false;
  }
}

void AfsControlPanel::handleAltValue() {
  const float increment = afsDiscreteInputs.altIncrement1000 ? 1000 : 100;

  if (inputEvents.ALT_dec) {
    altitudeDisplayValue -= increment;
  } else if (inputEvents.ALT_inc) {
    altitudeDisplayValue += increment;
  }

  altitudeDisplayValue =
      std::max(std::min(static_cast<int>(std::round(altitudeDisplayValue / increment) * increment), maxAltValue), minAltValue);
}

void AfsControlPanel::handleVerticalControl(double deltaTime, FmgcABus fmgcBus) {
  const bool isVerticalSelectedModeActive = fmgcBus.discreteWord1.bitFromValue(17) || fmgcBus.discreteWord1.bitFromValue(18);

  if (!vsFpaInDisplay && isVerticalSelectedModeActive) {
    vsFpaValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
    vsFpaInDisplay = true;
  }

  if (trkFpaActive) {
    if (vsFpaInDisplay && inputEvents.VS_FPA_dec) {
      vsFpaValue = std::max(std::min(std::roundf((vsFpaValue - 0.1) * 10) / 10, maxFpaValue), minFpaValue);
    } else if (vsFpaInDisplay && inputEvents.VS_FPA_inc) {
      vsFpaValue = std::max(std::min(std::roundf((vsFpaValue + 0.1) * 10) / 10, maxFpaValue), minFpaValue);
    } else if (!vsFpaInDisplay && (inputEvents.VS_FPA_inc || inputEvents.VS_FPA_dec)) {
      vsFpaValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
      vsFpaInDisplay = true;
    }
  } else {
    if (vsFpaInDisplay && inputEvents.VS_FPA_dec) {
      vsFpaValue = std::max(std::min(std::roundf((vsFpaValue - 100) / 100) * 100, maxVsValue), minVsValue);
    } else if (vsFpaInDisplay && inputEvents.VS_FPA_inc) {
      vsFpaValue = std::max(std::min(std::roundf((vsFpaValue + 100) / 100) * 100, maxVsValue), minVsValue);
    } else if (!vsFpaInDisplay && (inputEvents.VS_FPA_inc || inputEvents.VS_FPA_dec)) {
      vsFpaValue = trkFpaActive ? fmgcBus.track.value() : fmgcBus.heading.value();
      vsFpaInDisplay = true;
    }
  }

  if (!isVerticalSelectedModeActive && (inputEvents.VS_FPA_inc || inputEvents.VS_FPA_dec)) {
    vsFpaTimer.update(false, deltaTime);
  }

  if (vsFpaInDisplay && !isVerticalSelectedModeActive) {
    vsFpaTimer.update(true, deltaTime);
  } else if (isVerticalSelectedModeActive) {
    vsFpaTimer.update(false, deltaTime);
  }

  if (vsFpaTimer.getOutput() && vsFpaInDisplay && !isVerticalSelectedModeActive) {
    vsFpaValue = 0;
    vsFpaInDisplay = false;
  }
}

Arinc429DiscreteWord AfsControlPanel::getFcuWord1() {
  outWord1.setSsm(NormalOperation);
  outWord1.setBit(11, inputEvents.SPEED_MACH_push);
  outWord1.setBit(12, inputEvents.SPEED_MACH_pull);
  outWord1.setBit(13, inputEvents.ALT_inc || inputEvents.ALT_dec);
  outWord1.setBit(14, inputEvents.VS_FPA_inc || inputEvents.VS_FPA_dec);
  outWord1.setBit(15, inputEvents.SPEED_MACH_inc || inputEvents.SPEED_MACH_dec);
  outWord1.setBit(16, inputEvents.VS_FPA_push);
  outWord1.setBit(17, inputEvents.ALT_push);
  outWord1.setBit(18, inputEvents.ALT_pull);
  outWord1.setBit(19, inputEvents.VS_FPA_pull);
  outWord1.setBit(20, altInMeters);
  outWord1.setBit(21, inputEvents.SPD_MACH_MODE_push);
  outWord1.setBit(22, inputEvents.EXPED_push);
  outWord1.setBit(23, inputEvents.APPR_push);
  outWord1.setBit(24, !trkFpaActive);
  outWord1.setBit(25, trkFpaActive);

  return outWord1;
}

Arinc429DiscreteWord AfsControlPanel::getFcuWord2() {
  outWord2.setSsm(NormalOperation);
  outWord2.setBit(11, inputEvents.HDG_TRK_push);
  outWord2.setBit(12, inputEvents.HDG_TRK_pull);
  outWord2.setBit(13, inputEvents.LOC_push);
  outWord2.setBit(14, inputEvents.HDG_TRK_inc || inputEvents.HDG_TRK_dec);
  // The rest of the bits are set in Fcu.cpp directly.

  return outWord2;
}
