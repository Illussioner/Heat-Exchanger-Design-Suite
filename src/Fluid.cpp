#include "Fluid.h"
#include <iostream>
#include <stdexcept>
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

  if (massFlowRate <= 0)
  {
    throw std::invalid_argument("Mass flow rate must be positive.");
  }

  std::cout << "Inlet Temperature (" << "\u00B0" << "C): ";
  std::cin >> inletTemperature;

  std::cout << "Outlet Temperature (" << "\u00B0" << "C): ";
  std::cin >> outletTemperature;

  std::cout << "Specific Heat Cp (kJ/kg.K): ";
  std::cin >> specificHeat;

  if (specificHeat <= 0)
  {
    throw std::invalid_argument("Specific heat must be positive.");
  }
}

double Fluid::heatDuty() const
{
  return massFlowRate * specificHeat *
         (inletTemperature - outletTemperature);
}