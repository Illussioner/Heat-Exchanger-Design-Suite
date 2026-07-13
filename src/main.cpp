#include <iostream>
#include "HeatExchanger.h"
#include <locale> // Required for setlocale
int main()
{
  std::setlocale(LC_ALL, ".UTF-8");

  std::cout << "=====================================================\n";
  std::cout << "           Heat Exchanger Design Suite\n";
  std::cout << "                    Version 1.0.0\n";
  std::cout << "=====================================================\n\n";

  char again;

  do
  {
    try
    {
      HeatExchanger exchanger;

      exchanger.inputData();

      exchanger.calculate();
    }
    catch (const std::exception &e)
    {
      std::cerr << "\nError : "
                << e.what()
                << "\n";
    }

    std::cout << "\n-------------------------------------------\n";

    std::cout << "Perform another calculation? (Y/N): ";

    std::cin >> again;

    std::cout << "\n";

  } while (again == 'y' || again == 'Y');

  std::cout << "\nThank you for using Heat Exchanger Design Suite.\n";

  return 0;
}