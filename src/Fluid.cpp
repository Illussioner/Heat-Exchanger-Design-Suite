#include "Fluid.h"
#include <iostream>

Fluid::Fluid()
{
  name = "";
  massFlowRate = 0;
  inletTemperature = 0;
  outletTemperature = 0;
  specificHeat = 0;
}

void Fluid::input()
{
  std::cout << "\nEnter Fluid Name: ";
  std::getline(std::cin >> std::ws, name);

  std::cout << "Mass Flow Rate (kg/s): ";
  std::cin >> massFlowRate;

  std::cout << "Inlet Temperature (°C): ";
  std::cin >> inletTemperature;

  std::cout << "Outlet Temperature (°C): ";
  std::cin >> outletTemperature;

  std::cout << "Specific Heat Cp (kJ/kg.K): ";
  std::cin >> specificHeat;
}

double Fluid::heatDuty() const
{
  return massFlowRate * specificHeat *
         (inletTemperature - outletTemperature);
}