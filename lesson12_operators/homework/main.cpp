#include <iostream>
#include "vector/vector.hpp"

int main() {
  my_containers::Vector<int> numbers({0, 1,2,3,4,5,6,7,8,9});

  std::cout << numbers << std::endl;
  std::cout << numbers.size() << std::endl;

  numbers.erase(3);
  numbers.erase(4);
  numbers.erase(5);

  std::cout << numbers << std::endl;

  numbers.insert(1, 10);
  std::cout << numbers << std::endl;

  numbers.insert(5, 20);
  std::cout << numbers << std::endl;  

  numbers.push_back(30);
  std::cout << numbers << std::endl;

  return 0;
}