#ifndef FLUID_H
#define FLUID_H

#include <string>

class Fluid
{
public:
  std::string name;
  double massFlowRate;
  double inletTemperature;
  double outletTemperature;
  double specificHeat;

  Fluid(); // this is a constructor 
 
  void input(); // these are methods

  double heatDuty() const;
};

#endif