#include <fstream>
#include <ios>
#include "choose_number.hpp"

ChooseNumber::ChooseNumber() 
  : user_name_("")
  , max_value_(100)
  , target_value_(GetRandomValue())
  , attempts_count_(0)
  , scores_table_() {}

int ChooseNumber::GetRandomValue() const {
  std::srand(std::time(nullptr));
  return std::rand() % max_value_;
}

void ChooseNumber::Process() {
  CheckUserGuess();

  if (!ShowHighScoresTable())
    std::cerr << "Cannot add score of " << user_name_ << std::endl;
}

void ChooseNumber::CheckUserGuess() {
  int current_value = 0;
  std::cout << "Enter your guess (min: 0, max: "<< (max_value_ - 1) << "):" << std::endl;

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

bool ChooseNumber::ShowHighScoresTable() {
  if (!AddToTable())
    return false;

  std::cout << "" << std::endl;
  return ShowTable();
}

bool ChooseNumber::AddToTable() {
  std::ofstream out_file{kHighScoresFilename.data(), std::ios_base::app};
  if (!out_file.is_open()) {
    std::cout << "Failed to open file for write: " << kHighScoresFilename << "!" << std::endl;
    return false;
  }

  // Append new results to the table:
  out_file << user_name_ << ' ';
  out_file << attempts_count_;
  out_file << std::endl;

  return true;
}

bool ChooseNumber::ShowTable() {
	// Read the high score file and print all results
  std::ifstream in_file{kHighScoresFilename.data()};
  if (!in_file.is_open()) {
    std::cout << "Failed to open file for read: " << kHighScoresFilename << "!" << std::endl;
    return false;
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

    auto it = scores_table_.find(username);
    if (it == scores_table_.end())
      scores_table_.emplace(username, high_score);
    else if (it->second > high_score)
      it->second = high_score;
  }

  for (auto& el : scores_table_)
    std::cout << el.first << '\t' << el.second << std::endl;

  return true;
}

void ChooseNumber::SetMaxValue(const int value) {
  max_value_ = value;
  target_value_ = GetRandomValue();
}

void ChooseNumber::SetUserName(std::string name) {
  user_name_ = std::move(name);
}