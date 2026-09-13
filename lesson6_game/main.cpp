#include "choose_number.hpp"

int main(int argc, char **argv) {
  ChooseNumber game{};

  game.CheckIncomingParameters(argc, argv);
  game.Process();

  return 0;
}
