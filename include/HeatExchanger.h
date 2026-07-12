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
};

#endif