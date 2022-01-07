#pragma once

struct FmgcDiscreteInputs {
  bool apFcuCommand;

  bool apInstDisc;

  bool apOppEngaged;

  bool athrFcuCommand;

  bool athrInstDisc;

  bool athrOppEngaged;

  bool fdOppEngaged;

  bool powerSupplySplit;

  bool fcuOppHealthy;

  bool fcuOwnHealthy;

  bool facOppHealthy;

  bool facOwnHealthy;

  bool fmgcOppHealthy;

  bool fwcOppValid;

  bool fwcOwnValid;

  bool pfdOppValid;

  bool pfdOwnValid;

  bool adc3Switch;

  bool ir3Switch;

  bool leftWheelSpdGr70kts;

  bool rightWheelSpdGr70kts;

  bool bscuOppValid;

  bool bscuOwnValid;

  bool noseGearOppPressed;

  bool noseGearOwnPressed;

  bool elacOppApDisc;

  bool elacOwnApDisc;

  bool engineOppStopped;

  bool engineOwnStopped;
};

struct FmgcDiscreteOutputs {
  bool fcuFail;

  bool fmgcHealthy;

  bool ilsTestInhibit;

  bool stickLock;

  bool fdOwnEngaged;

  bool apOwnEngaged;

  bool athrOwnEngaged;
};
