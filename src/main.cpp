#include <iostream>
#include "HeatExchanger.h"

int main()
{
  std::cout << "=================================\n";
  std::cout << " Heat Exchanger Design Suite\n";
  std::cout << "=================================\n";

  HeatExchanger exchanger;

  exchanger.inputData();

  exchanger.calculate();

  return 0;
}