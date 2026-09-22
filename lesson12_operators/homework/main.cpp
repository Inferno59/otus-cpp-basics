#include <iostream>
#include <iterator>

#include "vector/vector.hpp"
#include "list/list.hpp"

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

  std::cout << "" << std::endl;
  std::cout << "Show current vector by iterator loop" << std::endl;
  for(auto it = numbers.begin(); it != numbers.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;

  for(auto it = numbers.begin(); it != numbers.end();) {
    it = numbers.erase(it);
  }

  std::cout << "After erase: " << numbers.size() << std::endl;
  for(auto it = numbers.begin(); it != numbers.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl; 

  auto it_begin = numbers.begin();
  for(size_t i = 0; i < 60; ++i) {
    it_begin = numbers.insert(it_begin, i);
    ++it_begin;
  }

  std::cout << numbers.size() << std::endl;

  for(auto it = numbers.begin(); it != numbers.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;  

  std::cout << "" << std::endl;
  std::cout << "Check ctor and operators" << std::endl;
  my_containers::Vector<int> tmp{1,2,3,4,5};
  
  my_containers::Vector<int> copy_ctor_vector(tmp);
  my_containers::Vector<int> move_ctor_vector_1(std::move(tmp));
  my_containers::Vector<int> move_ctor_vector_2(std::move(my_containers::Vector<int>{9,8,7}));

  std::cout << "copy_ctor_vector: " << copy_ctor_vector << std::endl;
  std::cout << "move_ctor_vector_1: " << move_ctor_vector_1 << std::endl;

  my_containers::Vector<int> copy_operator_vector;
  copy_operator_vector = copy_ctor_vector;

  my_containers::Vector<int> move_operator_vector;
  move_operator_vector = std::move(copy_ctor_vector);

  std::cout << "copy_operator_vector: " << copy_operator_vector << std::endl;
  std::cout << "move_operator_vector: " << move_operator_vector << std::endl;  


  std::cout << "" << std::endl;
  std::cout << "============================" << std::endl;
  std::cout << "List" << std::endl;
  my_containers::List<int> list_numbers({0, 1,2,3,4,5,6,7,8,9});

  std::cout << list_numbers << std::endl;
  std::cout << list_numbers.size() << std::endl;

  list_numbers.erase(std::next(list_numbers.begin(), 2));
  list_numbers.erase(std::next(list_numbers.begin(), 3));
  list_numbers.erase(std::next(list_numbers.begin(), 4));

  std::cout << list_numbers << std::endl;

  list_numbers.insert(list_numbers.begin(), 10);
  std::cout << list_numbers << std::endl;

  list_numbers.insert(std::next(list_numbers.begin(), 4), 20);
  std::cout << list_numbers << std::endl;  

  list_numbers.push_back(30);
  std::cout << list_numbers << std::endl;

  std::cout << "" << std::endl;
  std::cout << "Show current list by iterator loop" << std::endl;
  for(auto it = list_numbers.begin(); it != list_numbers.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;

  for(auto it = list_numbers.begin(); it != list_numbers.end();) {
    it = list_numbers.erase(it);
  }

  std::cout << "After erase: " <<  list_numbers.size() << std::endl;

  auto list_begin = list_numbers.begin();
  for(size_t i = 0; i < 60; ++i) {
    list_begin = list_numbers.insert(list_begin, i);
    ++list_begin;
  }

  std::cout << list_numbers.size() << std::endl;

  for(auto it = list_numbers.begin(); it != list_numbers.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;  

  std::cout << "" << std::endl;
  std::cout << "Check ctor and operators" << std::endl;
  my_containers::List<int> tmp_list{1,2,3,4,5};
  
  my_containers::List<int> copy_ctor_list(tmp_list);
  my_containers::List<int> move_ctor_list_1(std::move(tmp_list));
  my_containers::List<int> move_ctor_list_2(std::move(my_containers::List<int>{9,8,7}));

  std::cout << "copy_ctor_list: " << copy_ctor_list << std::endl;
  std::cout << "move_ctor_list_1: " << move_ctor_list_1 << std::endl;

  my_containers::List<int> copy_operator_list;
  copy_operator_list = copy_ctor_list;

  my_containers::List<int> move_operator_list;
  move_operator_list = std::move(copy_ctor_list);

  std::cout << "copy_operator_list: " << copy_operator_list << std::endl;
  std::cout << "move_operator_list: " << move_operator_list << std::endl;  

  return 0;
}