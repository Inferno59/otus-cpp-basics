#include <iostream>
#include "vector/vector.hpp"

class Test {
public:
  Test() {
    std::cout << "Test ctor" << std::endl;
  }

  ~Test() {
    std::cout << "Test dtor" << std::endl;
  }  

  friend std::ostream& operator<<(std::ostream& os, const Test& src) {
    return os << "Test";
  }
  
};

int main() {
  // my_containers::Vector<int> numbers({0, 1,2,3,4,5,6,7,8,9});

  // std::cout << numbers << std::endl;
  // std::cout << numbers.size() << std::endl;

  Test test;
  my_containers::Vector<Test> tests({test, test});
  
  // for(size_t i = 0; i < tests.size(); ++i) {
  //   std::cout << tests[i] << std::endl;     
  // }
  //std::cout << tests << std::endl;
  std::cout << tests.size() << std::endl;  
  return 0;
}