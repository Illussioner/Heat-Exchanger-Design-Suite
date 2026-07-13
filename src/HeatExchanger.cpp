#include "HeatExchanger.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Report.h"
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
  double Cmin = calculateCMin();
  double Cmax = calculateCMax();
  double NTU = calculateNTU(area);
  double effectiveness = calculateEffectiveness();

  std::ostringstream report;
  report << std::fixed
         << std::setprecision(2);
  report
      << "\n=====================================================\n";

  report
      << "                DESIGN RESULTS\n";

  report
      << "=====================================================\n\n";

  report << std::left
         << std::setw(25)
         << "Heat Duty"
         << ": "
         << Qhot
         << " kW\n";

  report << std::left
         << std::setw(25)
         << "LMTD"
         << ": "
         << lmtd
         << " " << "\u00B0" << "C\n";

  report << std::left
         << std::setw(25)
         << "Required Area"
         << ": "
         << area
         << " m" << "\u00B2" << "\n";

  report << std::left
         << std::setw(25)
         << "Minimum Heat Capacity"
         << ": "
         << Cmin
         << " kW/K\n";

  report << std::left
         << std::setw(25)
         << "Maximum Heat Capacity"
         << ": "
         << Cmax
         << " kW/K\n";

  report << std::left
         << std::setw(25)
         << "Capacity Ratio"
         << ": "
         << Cmin / Cmax
         << "\n";

  report << std::left
         << std::setw(25)
         << "NTU"
         << ": "
         << NTU
         << "\n";

  report << std::left
         << std::setw(25)
         << "Effectiveness"
         << ": "
         << effectiveness
         << "\n";

  report << "\n=====================================================\n";
  std::cout << report.str();
  Report::save("../reports/Report.txt", report.str());
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

double HeatExchanger::calculateCMin() const
{
  double Ch = hotFluid.massFlowRate * hotFluid.specificHeat;
  double Cc = coldFluid.massFlowRate * coldFluid.specificHeat;

  return std::min(Ch, Cc);
}

double HeatExchanger::calculateCMax() const
{
  double Ch = hotFluid.massFlowRate * hotFluid.specificHeat;
  double Cc = coldFluid.massFlowRate * coldFluid.specificHeat;

  return std::max(Ch, Cc);
}

double HeatExchanger::calculateNTU(double area) const
{
  return (overallU * area) / calculateCMin();
}

double HeatExchanger::calculateCounterFlowEffectiveness(double NTU, double Cr) const
{
  return (1-std::exp(-NTU * (1-Cr)))
  /
  (1-Cr*std::exp(-NTU*(1 - Cr)));
}

double HeatExchanger::calculateParallelFlowEffectiveness(double NTU, double Cr) const
{
  return (1 - std::exp(-NTU * ( 1 + Cr)))
  /
  (1 + Cr);
}

double HeatExchanger::calculateEffectiveness() const
{
  double area = calculateArea(std::abs(hotFluid.heatDuty()),calculateLMTD());

  double NTU = calculateNTU(area);

  double Cr = calculateCMin() / calculateCMax();

  switch(flowtype){
    case FlowType::Counter:
      return calculateCounterFlowEffectiveness(NTU, Cr);
    case FlowType::Parallel:
      return calculateParallelFlowEffectiveness(NTU, Cr);
  }
  return 0.0;
}

