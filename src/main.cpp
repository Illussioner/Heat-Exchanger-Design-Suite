  #include <iostream>
  #include "HeatExchanger.h"
  #include <locale> // Required for setlocale
  #include <windows.h>

  void setColor(WORD color)
  {
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color);
  }
  enum ConsoleColor
  {
    BLACK = 0,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    YELLOW = 14,
    WHITE = 15
  };
  int main()
  {
    std::setlocale(LC_ALL, ".UTF-8");
    setColor(CYAN);
    std::cout << "=====================================================\n";
    std::cout << "           Heat Exchanger Design Suite\n";
    std::cout << "                    Version 1.0.0\n";
    std::cout << "=====================================================\n\n";
    setColor(WHITE);

    char again;

    do
    {
      try
      {
        HeatExchanger exchanger;

        exchanger.inputData();

        exchanger.calculate();
        setColor(GREEN);

        std::cout
            << "\n " << "\u2713" << " Analysis Completed Successfully\n";

        std::cout
            << " " << "\u2713" << " Report Generated Successfully\n";

        setColor(WHITE);
      }
      catch (const std::exception &e)
      {
        setColor(RED);
        std::cerr << "\nError : "
                  << e.what()
                  << "\n";
        setColor(WHITE);
      }

      setColor(CYAN);

      std::cout
          << "\n=====================================================\n";

      setColor(WHITE);

      setColor(YELLOW);

      std::cout
          << "Perform another calculation? (Y/N): ";

      setColor(WHITE);

      std::cin >> again;

      std::cout << "\n";

    } while (again == 'y' || again == 'Y');

    setColor(CYAN);

    std::cout
        << "\n=====================================================\n";
    std::cout
        << " Thank you for using Heat Exchanger Design Suite\n";
    std::cout
        << "=====================================================\n";

    setColor(WHITE);

    return 0;
  }