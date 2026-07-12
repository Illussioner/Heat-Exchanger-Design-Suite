#ifndef HEATEXCHANGER_H
#define HEATEXCHANGER_H

#include "Fluid.h"
enum class FlowType
{
  Counter,
  Parallel
};

class HeatExchanger
{
private:
  Fluid hotFluid;
  Fluid coldFluid;
  
  double overallU;

  FlowType flowtype;
public:
  HeatExchanger();

  void inputData();

  void calculate();

  double calculateLMTD() const;

  double calculateArea(double heatDuty, double lmtd) const;

  double calculateCMin() const;

  double calculateCMax() const;

  double calculateNTU(double area) const;

  double calculateCounterFlowEffectiveness(double NTU, double Cr) const;

  double calculateParallelFlowEffectiveness(double NTU, double Cr) const;

  double calculateEffectiveness() const;
};

#endif