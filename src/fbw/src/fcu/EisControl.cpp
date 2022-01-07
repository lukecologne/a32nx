#include "EisControl.h"
#include <algorithm>
#include <cmath>

// These macros are defined in a MSFS header file, and have to be undef'd because they seem to shadow the std::max/min
// functions, which is obviously bad
#undef min
#undef max

EisControlPanel::EisControlPanel() {}

void EisControlPanel::init() {
  selectedFilter = EfisFilterSelection::NONE;
  lsActive = false;
  fdActive = true;

  barohPaValue = 1013;
  baroInHgValue = 29.92;
  baroIsStd = false;
  baroIsQfe = false;
}

void EisControlPanel::step() {
  if (inputEvents.FD_push) {
    fdActive = !fdActive;
  }

  if (inputEvents.LS_push) {
    lsActive = !lsActive;
  }

  if (inputEvents.FILTER_push != 0) {
    EfisFilterSelection filterEventValue = static_cast<EfisFilterSelection>(inputEvents.FILTER_push);
    if (filterEventValue == selectedFilter) {
      selectedFilter = EfisFilterSelection::NONE;
    } else {
      selectedFilter = filterEventValue;
    }
  }

  if (inputEvents.BARO_pull) {
    baroIsStd = true;
  } else if (inputEvents.BARO_push && baroIsStd) {
    baroIsStd = false;
  } else if (inputEvents.BARO_push && !baroIsStd) {
    baroIsQfe = !baroIsQfe;
  }

  if (!baroIsStd && discreteInputs.baroIsInhg) {
    if (inputEvents.BARO_dec) {
      baroInHgValue = std::min(std::max(round((baroInHgValue - 0.01f) * 100.0f) / 100.0f, minInHgValue), maxInHgValue);
    }
    if (inputEvents.BARO_inc) {
      baroInHgValue = std::min(std::max(round((baroInHgValue + 0.01f) * 100.0f) / 100.0f, minInHgValue), maxInHgValue);
    }
    barohPaValue = round(baroInHgValue * inHg2hPa);
  } else if (!baroIsStd && !discreteInputs.baroIsInhg) {
    if (inputEvents.BARO_dec) {
      barohPaValue = std::min(std::max(barohPaValue - 1, minHPAValue), maxHPAValue);
    }
    if (inputEvents.BARO_inc) {
      barohPaValue = std::min(std::max(barohPaValue + 1, minHPAValue), maxHPAValue);
    }
    baroInHgValue = round(barohPaValue * hPa2InHg * 100.0f) / 100.0f;
  }
}

Arinc429DiscreteWord EisControlPanel::getEisWord1() {
  outWord1.setSsm(NormalOperation);
  outWord1.setBit(11, discreteInputs.baroIsInhg);
  outWord1.setBit(25, discreteInputs.efisRange == EfisRangeSelection::RANGE10);
  outWord1.setBit(26, discreteInputs.efisRange == EfisRangeSelection::RANGE20);
  outWord1.setBit(27, discreteInputs.efisRange == EfisRangeSelection::RANGE40);
  outWord1.setBit(28, discreteInputs.efisRange == EfisRangeSelection::RANGE80);
  outWord1.setBit(29, discreteInputs.efisRange == EfisRangeSelection::RANGE160);
  return outWord1;
}

Arinc429DiscreteWord EisControlPanel::getEisWord2() {
  outWord2.setSsm(NormalOperation);
  outWord2.setBit(11, discreteInputs.efisMode == EfisModeSelection::PLAN);
  outWord2.setBit(12, discreteInputs.efisMode == EfisModeSelection::ARC);
  outWord2.setBit(13, discreteInputs.efisMode == EfisModeSelection::ROSE_NAV);
  outWord2.setBit(14, discreteInputs.efisMode == EfisModeSelection::ROSE_VOR);
  outWord2.setBit(15, discreteInputs.efisMode == EfisModeSelection::ROSE_ILS);
  outWord2.setBit(17, selectedFilter == EfisFilterSelection::CSTR);
  outWord2.setBit(18, selectedFilter == EfisFilterSelection::WPT);
  outWord2.setBit(19, selectedFilter == EfisFilterSelection::VORD);
  outWord2.setBit(20, selectedFilter == EfisFilterSelection::NDB);
  outWord2.setBit(21, selectedFilter == EfisFilterSelection::ARPT);
  outWord2.setBit(22, lsActive);
  outWord2.setBit(23, !fdActive);
  outWord2.setBit(24, discreteInputs.navaid1Mode == NavaidSelection::ADF);
  outWord2.setBit(25, discreteInputs.navaid2Mode == NavaidSelection::ADF);
  outWord2.setBit(26, discreteInputs.navaid1Mode == NavaidSelection::VOR);
  outWord2.setBit(27, discreteInputs.navaid2Mode == NavaidSelection::VOR);
  outWord2.setBit(28, baroIsStd);
  outWord2.setBit(29, !baroIsQfe);
  return outWord2;
}
