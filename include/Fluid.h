#ifndef FLUID_H
#define FLUID_H

#include <string>

class Fluid
{
private:
  

public:
  std::string name;

  double massFlowRate;

  double inletTemperature;

  double outletTemperature;

  double specificHeat;
  Fluid();
};

#endif