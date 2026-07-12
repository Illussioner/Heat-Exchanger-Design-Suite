#include "HeatExchanger.h"
#include <iostream>
#include <cmath>
#include <iomanip>

HeatExchanger::HeatExchanger()
{
}
void HeatExchanger::inputData()
{
  std::cout << "\n===== HOT FLUID =====\n";
  hotFluid.input();
  if (hotFluid.inletTemperature <= hotFluid.outletTemperature)
  {
    throw std::invalid_argument(
        "Hot fluid inlet temperature must be greater than outlet temperature.");
  }

  std::cout << "\n===== COLD FLUID =====\n";
  coldFluid.input();
  if (coldFluid.inletTemperature >= coldFluid.outletTemperature)
  {
    throw std::invalid_argument(
        "Cold fluid outlet temperature must be greater than inlet temperature.");
  }

  std::cout << "\nOverall Heat Transfer Coefficient U (kW/m" << "\u00B2" << ".K): ";
  std::cin >> overallU;

  int choice;

  std::cout << "\nFlow Arrangement\n";
  std::cout << "1. Counter Flow\n";
  std::cout << "2. Parallel Flow\n";
  std::cout << "Choice : ";

  std::cin >> choice;

  flowtype = (choice == 1) ? FlowType::Counter : FlowType::Parallel;
}

void HeatExchanger::calculate()
{
  double Qhot = std::abs(hotFluid.heatDuty());
  double Qcold = std::abs(coldFluid.heatDuty());
  if (std::abs(Qhot - Qcold) > 5.0)
  {
    std::cout
        << "\nWarning: Energy balance mismatch.\n";
  }
  
  double lmtd = calculateLMTD();
  double area = calculateArea (Qhot, lmtd);
  std::cout << "\n=================================\n";

  std::cout
    << "Heat Duty :"
    << std::fixed << std::setprecision(2)
    << Qhot
    <<"kW\n";

  std::cout
      << "LMTD : "
      << std::fixed << std::setprecision(2)
      << lmtd
      << " " << "\u00B0" << "C\n";

  std::cout
      << "Required Area : "
      << std::fixed << std::setprecision(2)
      << area
      << " m" << "\u00B2" << "\n";
}

double HeatExchanger::calculateLMTD() const{
  double deltaT1;
  double deltaT2;

  if(flowtype == FlowType::Counter){
    deltaT1 = hotFluid.inletTemperature - coldFluid.outletTemperature;

    deltaT2 = hotFluid.outletTemperature - coldFluid.inletTemperature;
  }

  else{
    deltaT1 = hotFluid.inletTemperature-coldFluid.inletTemperature;

    deltaT2 = hotFluid.outletTemperature - coldFluid.outletTemperature;
  }
  if (deltaT1 <= 0 || deltaT2 <= 0)
  {
    throw std::runtime_error("Invalid temperature difference.");
  }

  if (std::abs(deltaT1 - deltaT2) < 1e-9)
  {
    return deltaT1;
  }
  return (deltaT1 - deltaT2) / std::log(deltaT1/ deltaT2);
};

double HeatExchanger::calculateArea(double heatDuty, double lmtd) const {
  return heatDuty / (overallU * lmtd);
};
