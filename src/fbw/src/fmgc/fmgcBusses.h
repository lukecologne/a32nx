#pragma once

#include "../busStructures/busStructures.h"

struct FmgcBusInputs {
  FmgcABus fmgcOpp;
  FacBus facOwn;
  FacBus facOpp;
  AdirsBusses adirsOwn;
  AdirsBusses adirsOpp;
  AdirsBusses adirs3;
  FadecBus fadecOpp;
  FadecBus fadecOwn;
  FcdcBus fcdcOwn;
  FcdcBus fcdcOpp;
  RaBus raOwn;
  RaBus raOpp;
  DmeBus dmeOwn;
  DmeBus dmeOpp;
  IlsBus ilsOwn;
  IlsBus ilsOpp;
  FcuBus fcuOwn;
};
