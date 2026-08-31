#include "choose_number.hpp"

int main(int argc, char **argv) {
	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

  ChooseNumber game(std::move(user_name));

  game.Process();

  return 0;
}
