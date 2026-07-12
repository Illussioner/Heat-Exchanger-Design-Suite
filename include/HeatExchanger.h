#ifndef HEATEXCHANGER_H
#define HEATEXCHANGER_H

#include "Fluid.h"

class HeatExchanger
{
private:
  Fluid hotFluid;

  Fluid coldFluid;

public:
  HeatExchanger();
};

#endif