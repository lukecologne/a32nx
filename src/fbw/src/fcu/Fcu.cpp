#include "Fcu.h"

Fcu::Fcu() {
  afsControl = AfsControlPanel();
  eisControl[0] = EisControlPanel();
  eisControl[1] = EisControlPanel();
};

void Fcu::init() {
  afsControl.init();
  eisControl[0].init();
  eisControl[1].init();
};

void Fcu::step(double deltaTime, bool dcBus2Active, bool dcEssBusActive) {
  computeFmgcPriority();

  afsControl.inputEvents = inputEvents.AFS;
  afsControl.afsDiscreteInputs = discreteInputs.afsDiscretes;
  afsControl.step(deltaTime, fmgc1HasPriority ? fmgc1BusInput : fmgc2BusInput);
  eisControl[0].inputEvents = inputEvents.EIS_LEFT;
  eisControl[0].discreteInputs = discreteInputs.efisLeftDiscretes;
  eisControl[0].step();
  eisControl[1].inputEvents = inputEvents.EIS_RIGHT;
  eisControl[1].discreteInputs = discreteInputs.efisRightDiscretes;
  eisControl[1].step();

  writeOutputs();
}

void Fcu::computeFmgcPriority() {
  if ((discreteInputs.afsDiscretes.ap2Engaged && !discreteInputs.afsDiscretes.ap1Engaged) ||
      (discreteInputs.afsDiscretes.fd2Engaged && !discreteInputs.afsDiscretes.fd1Engaged && !discreteInputs.afsDiscretes.ap1Engaged) ||
      (discreteInputs.afsDiscretes.athr2Engaged && !discreteInputs.afsDiscretes.athr1Engaged && !discreteInputs.afsDiscretes.fd1Engaged &&
       !discreteInputs.afsDiscretes.ap1Engaged)) {
    fmgc1HasPriority = false;
  } else {
    fmgc1HasPriority = true;
  }
}

void Fcu::writeOutputs() {
  // Write Discrete outputs
  fcuDiscreteOutputs.fcu1Healthy = true;
  fcuDiscreteOutputs.fcu2Healthy = true;

  fcuDiscreteOutputs.ap1LightOn = discreteInputs.afsDiscretes.ap1Engaged && fmgc1BusInput.discreteWord4.bitFromValue(12);
  fcuDiscreteOutputs.ap2LightOn = discreteInputs.afsDiscretes.ap2Engaged && fmgc2BusInput.discreteWord4.bitFromValue(12);
  fcuDiscreteOutputs.athrLightOn = fmgc1HasPriority
                                       ? discreteInputs.afsDiscretes.athr1Engaged && fmgc1BusInput.discreteWordAthr.bitFromValue(13)
                                       : discreteInputs.afsDiscretes.athr2Engaged && fmgc2BusInput.discreteWordAthr.bitFromValue(13);

  FmgcABus fmgcPriorityBus = fmgc1HasPriority ? fmgc1BusInput : fmgc2BusInput;

  fcuDiscreteOutputs.locLightOn = (fmgcPriorityBus.discreteWord3.bitFromValue(16) || fmgcPriorityBus.discreteWord2.bitFromValue(13) ||
                                   fmgcPriorityBus.discreteWord2.bitFromValue(14)) &&
                                  !(fmgcPriorityBus.discreteWord3.bitFromValue(22) || fmgcPriorityBus.discreteWord4.bitFromValue(14));
  fcuDiscreteOutputs.expedLightOn = fmgcPriorityBus.discreteWord1.bitFromValue(24);
  fcuDiscreteOutputs.apprLightOn = fmgcPriorityBus.discreteWord3.bitFromValue(20) || fmgcPriorityBus.discreteWord4.bitFromValue(14);

  for (int i = 0; i < 2; i++) {
    fcuDiscreteOutputs.eisDiscreteOut[i].fdLightActive = eisControl[i].fdActive;
    fcuDiscreteOutputs.eisDiscreteOut[i].lsLightActive = eisControl[i].lsActive;
    fcuDiscreteOutputs.eisDiscreteOut[i].cstrLightActive = eisControl[i].selectedFilter == EfisFilterSelection::CSTR;
    fcuDiscreteOutputs.eisDiscreteOut[i].wptLightOn = eisControl[i].selectedFilter == EfisFilterSelection::WPT;
    fcuDiscreteOutputs.eisDiscreteOut[i].vorDLightOn = eisControl[i].selectedFilter == EfisFilterSelection::VORD;
    fcuDiscreteOutputs.eisDiscreteOut[i].ndbLightOn = eisControl[i].selectedFilter == EfisFilterSelection::NDB;
    fcuDiscreteOutputs.eisDiscreteOut[i].arptLightOn = eisControl[i].selectedFilter == EfisFilterSelection::ARPT;
  }

  // Write EIS outputs
  fcuBusOutput.fcuEisWord1Left = eisControl[0].getEisWord1();
  fcuBusOutput.fcuEisWord2Left = eisControl[0].getEisWord2();
  fcuBusOutput.fcuEisWord1Right = eisControl[1].getEisWord1();
  fcuBusOutput.fcuEisWord2Right = eisControl[1].getEisWord2();
  fcuBusOutput.baroCorrectionHpaLeft.setFromData(static_cast<float>(eisControl[0].barohPaValue), NormalOperation);
  fcuBusOutput.baroCorrectionHpaRight.setFromData(static_cast<float>(eisControl[1].barohPaValue), NormalOperation);
  fcuBusOutput.baroCorrectionInhgLeft.setFromData(eisControl[0].baroInHgValue, NormalOperation);
  fcuBusOutput.baroCorrectionInhgRight.setFromData(eisControl[1].baroInHgValue, NormalOperation);

  // Write FCU outputs
  fcuBusOutput.fcuDiscreteWord1 = afsControl.getFcuWord1();
  fcuBusOutput.fcuDiscreteWord2 = afsControl.getFcuWord2();
  fcuBusOutput.fcuDiscreteWord2.setBit(18, false);
  fcuBusOutput.fcuDiscreteWord2.setBit(19, false);
  fcuBusOutput.fcuDiscreteWord2.setBit(20, fmgc1HasPriority);
  fcuBusOutput.fcuDiscreteWord2.setBit(21, !fmgc1HasPriority);
  fcuBusOutput.fcuDiscreteWord2.setBit(24, true);
  fcuBusOutput.fcuDiscreteWord2.setBit(25, true);
  fcuBusOutput.fcuDiscreteWord2.setBit(26, !eisControl[0].fdActive);
  fcuBusOutput.fcuDiscreteWord2.setBit(27, !eisControl[1].fdActive);

  if (true) {
    fcuBusOutput.selectedAirspeed.setSsm(afsControl.speedMachInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedAirspeed.setData(afsControl.speedMachDisplayValue);

    fcuBusOutput.selectedMach.setSsm(NoComputedData);
    fcuBusOutput.selectedMach.setData(0);
  } else {
    fcuBusOutput.selectedMach.setSsm(afsControl.speedMachInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedMach.setData(afsControl.speedMachDisplayValue);

    fcuBusOutput.selectedAirspeed.setSsm(NoComputedData);
    fcuBusOutput.selectedAirspeed.setData(0);
  }

  if (afsControl.trkFpaActive) {
    fcuBusOutput.selectedHeading.setSsm(NoComputedData);
    fcuBusOutput.selectedHeading.setData(0);
    fcuBusOutput.selectedVerticalSpeed.setSsm(NoComputedData);
    fcuBusOutput.selectedVerticalSpeed.setData(0);

    fcuBusOutput.selectedTrack.setSsm(afsControl.headingTrackInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedTrack.setData(afsControl.headingTrackValue);
    fcuBusOutput.selectedFpa.setSsm(afsControl.vsFpaInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedFpa.setData(afsControl.vsFpaValue);
  } else {
    fcuBusOutput.selectedTrack.setSsm(NoComputedData);
    fcuBusOutput.selectedTrack.setData(0);
    fcuBusOutput.selectedFpa.setSsm(NoComputedData);
    fcuBusOutput.selectedFpa.setData(0);

    fcuBusOutput.selectedHeading.setSsm(afsControl.headingTrackInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedHeading.setData(afsControl.headingTrackValue);
    fcuBusOutput.selectedVerticalSpeed.setSsm(afsControl.vsFpaInDisplay ? NormalOperation : NoComputedData);
    fcuBusOutput.selectedVerticalSpeed.setData(afsControl.vsFpaValue);
  }
  fcuBusOutput.selectedAltitude.setSsm(NormalOperation);
  fcuBusOutput.selectedAltitude.setData(afsControl.altitudeDisplayValue);

  // Copy ATHR data from FMGC that has priority
  fcuBusOutput.fcuAtsWord = fmgc1HasPriority ? fmgc1BusInput.discreteWordAthr : fmgc2BusInput.discreteWordAthr;
  fcuBusOutput.fcuAtsFmaWord = fmgc1HasPriority ? fmgc1BusInput.discreteWordAthrFma : fmgc2BusInput.discreteWordAthrFma;
  fcuBusOutput.n1AthrCommand = {};
  fcuBusOutput.flexToTemp = {};
}

FcuBus Fcu::getBusOutput() {
  return fcuBusOutput;
}

FcuDiscreteOutputs Fcu::getDiscreteOutputs() {
  return fcuDiscreteOutputs;
}
