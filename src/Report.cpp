#include "Report.h"
#include <fstream>
#include <iostream>
void Report::save(const std::string& filename, const std::string& data)
{
  std::ofstream file(filename);

  if (!file)
  {
    std::cerr << "Error: Could not open " << filename << '\n';
    return;
  }
  file << data;
  std::cout << "\nReport saved to " << filename << '\n';
}