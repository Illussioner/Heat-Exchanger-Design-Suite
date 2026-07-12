#include "HeatExchanger.h"
#include <iostream>
#include <cmath>

HeatExchanger::HeatExchanger()
{
}
void HeatExchanger::inputData()
{
  std::cout << "\n===== HOT FLUID =====\n";
  hotFluid.input();

  std::cout << "\n===== COLD FLUID =====\n";
  coldFluid.input();
}

void HeatExchanger::calculate()
{
  double Qhot = hotFluid.heatDuty();

  std::cout << "\n=========================\n";
  std::cout << "Heat Duty = "
            << std::abs(Qhot)
            << " kW\n";
}