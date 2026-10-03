#include <iostream>
#include <string>
#include <sstream>

#include "include/statistics.hpp"

int main() {
  statistics::Statistics statistics;

  std::string line;
  while(std::getline(std::cin, line)) {
    if (line.empty())
      break;

    std::istringstream iss(line);
    while(iss) {
      double value = 0.0;
      while(iss >> value)
        statistics.update(value);

      // Почему цикл остановился?
      if (iss.fail() && !iss.eof()) {
          // fail() == true, но это НЕ конец строки — значит встретился мусор
          throw std::invalid_argument("Invalid input: not a number");
      }
    }
  }
    

  statistics.eval();

  return 0;
}