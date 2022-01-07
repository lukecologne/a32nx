#pragma once

enum class EfisModeSelection { ROSE_ILS, ROSE_VOR, ROSE_NAV, ARC, PLAN };

enum class EfisRangeSelection { RANGE10, RANGE20, RANGE40, RANGE80, RANGE160, RANGE320 };

enum class NavaidSelection { VOR, ADF, NONE };

struct EfisDiscreteInputs {
  EfisRangeSelection efisRange;

  EfisModeSelection efisMode;

  NavaidSelection navaid1Mode;

  NavaidSelection navaid2Mode;

  bool baroIsInhg;
};

struct AfsDiscreteInputs {
  bool fd1Engaged;

  bool fd2Engaged;

  bool ap1Engaged;

  bool ap2Engaged;

  bool athr1Engaged;

  bool athr2Engaged;

  bool altIncrement1000;
};

struct FcuDiscreteInputs {
  AfsDiscreteInputs afsDiscretes;

  EfisDiscreteInputs efisLeftDiscretes;

  EfisDiscreteInputs efisRightDiscretes;
};

struct FcuEisDiscreteOutputs {
  bool fdLightActive;

  bool lsLightActive;

  bool cstrLightActive;

  bool wptLightOn;

  bool vorDLightOn;

  bool ndbLightOn;

  bool arptLightOn;
};

struct FcuDiscreteOutputs {
  bool fcu1Healthy;

  bool fcu2Healthy;

  FcuEisDiscreteOutputs eisDiscreteOut[2];

  bool locLightOn;

  bool expedLightOn;

  bool apprLightOn;

  bool ap1LightOn;

  bool ap2LightOn;

  bool athrLightOn;
};
