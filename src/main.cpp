#include <iostream>
#include "HeatExchanger.h"
#include <locale> // Required for setlocale
int main()
{
  std::setlocale(LC_ALL, ".UTF-8");
  
  std::cout << "=================================\n";
  std::cout << " Heat Exchanger Design Suite\n";
  std::cout << " Version 1.0.0\n";
  std::cout << " Author : Ishan Jain\n";
  std::cout << "=================================\n";

  char again;

  do
  {
    try
    {
      HeatExchanger exchanger;

      exchanger.inputData();

      exchanger.calculate();

      std::cout
          << "\nPerform another calculation? (y/n): ";
      std::cin >> again;
    }
    catch (const std::exception &e)
    {
      std::cout
          << "\nError: "
          << e.what()
          << '\n';
    }
  } while (again == 'y' || again == 'Y');
  
  return 0;
}