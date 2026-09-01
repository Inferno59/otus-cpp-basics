#include "choose_number.hpp"

int main(int argc, char **argv) {
  ChooseNumber game{};

  bool just_show_table = false;
  if (argc >= 2) {
    if (std::string(argv[1]) == "-max") {
      int parameter_value = 0;
      if (argc < 3) {
        std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;    
      } else {
        game.SetMaxValue(std::stoi(argv[2]));
      }
    } else if (std::string(argv[1]) == "-table") {
      game.ShowTable();
      just_show_table = true;
    } else if (std::string(argv[1]) == "-level") {
      const int level = std::stoi(argv[2]);
      switch(std::stoi(argv[2])) {
        case 1: 
          game.SetMaxValue(10); 
          break;
        case 2: 
          game.SetMaxValue(50); 
          break;
        case 3: 
          game.SetMaxValue(100); 
          break;
        default:
          std::cerr << "Bad level " << level << " should be in range 1-3. Max value will be applied as default (100)" << std::endl;
      }
    }

  }

  if (!just_show_table) {
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;

    game.SetUserName(std::move(user_name));
    game.Process();
  }

  return 0;
}
