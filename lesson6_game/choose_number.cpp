#include <fstream>
#include <ios>
#include "choose_number.hpp"

ChooseNumber::ChooseNumber(std::string name) 
  : user_name_(std::move(name))
  , target_value_(GetRandomValue())
  , attempts_count_(0) {
  std::cout << "user_name_: " << user_name_ << std::endl;
}

int ChooseNumber::GetRandomValue() const {
  std::srand(std::time(nullptr)); // use current time as seed for random generator  
  return std::rand() % 100;
}

void ChooseNumber::Process() {
  CheckUserGuess();
  ShowHighScoresTable();
}

void ChooseNumber::CheckUserGuess() {
  int current_value = 0;
  std::cout << "Enter your guess:" << std::endl;

  do {
    std::cin >> current_value;

    ++attempts_count_;

    if (current_value < target_value_) {
      std::cout <<" less than" << std::endl;
    }
    else if (current_value > target_value_) {
      std::cout << "greater than " << std::endl;
    }
    else {
      std::cout << "you win! attempts = " << attempts_count_ << std::endl;
      break;
    }
  } while (true);
}

void ChooseNumber::ShowHighScoresTable() {
	// Write new high score to the records table
	{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		std::ofstream out_file{kHighScoresFilename.data(), std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << kHighScoresFilename << "!" << std::endl;
			return;
		}

		// Append new results to the table:
		out_file << user_name_ << ' ';
		out_file << attempts_count_;
		out_file << std::endl;
	} // end of score here just to mark end of the logic block of code

	// Read the high score file and print all results
	{
		std::ifstream in_file{kHighScoresFilename.data()};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << kHighScoresFilename << "!" << std::endl;
			return;
		}

		std::cout << "High scores table:" << std::endl;

		std::string username;
		int high_score = 0;
		while (true) {
			// Read the username first
			in_file >> username;
			// Read the high score next
			in_file >> high_score;
			// Ignore the end of line symbol
			in_file.ignore();

			if (in_file.fail()) {
				break;
			}

			// Print the information to the screen
			std::cout << username << '\t' << high_score << std::endl;
		}
  }
}