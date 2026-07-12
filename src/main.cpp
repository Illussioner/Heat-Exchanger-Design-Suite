#include <iostream>
#include "HeatExchanger.h"
#include <locale> // Required for setlocale
int main()
{
  std::setlocale(LC_ALL, ".UTF-8");
  
  std::cout << "=================================\n";
  std::cout << " Heat Exchanger Design Suite\n";
  std::cout << "=================================\n";

  try
  {
    HeatExchanger exchanger;

    exchanger.inputData();

    exchanger.calculate();
  }
  catch (const std::exception &e)
  {
    std::cout
    << "\nError: "
    << e.what()
    << '\n';
  }
  return 0;
}