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

  std::cout << "\nOverall Heat Transfer Coefficient U (kW/m².K): ";
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
  double heatDuty = std::abs(hotFluid.heatDuty());
  double lmtd = calculateLMTD();
  double area = calculateArea (heatDuty, lmtd);
  std::cout << "\n=================================\n";

  std::cout
    << "Heat Duty :"
    << heatDuty
    <<"kW\n";

  std::cout
      << "LMTD : "
      << lmtd
      << " °C\n";

  std::cout
      << "Required Area : "
      << area
      << " m²\n";
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

  return (deltaT1 - deltaT2) / std::log(deltaT1/ deltaT2);
};

double HeatExchanger::calculateArea(double heatDuty, double lmtd) const {
  return heatDuty / (overallU * lmtd);
};
