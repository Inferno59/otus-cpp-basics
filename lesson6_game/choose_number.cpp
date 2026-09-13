#include <fstream>
#include <ios>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <utility>

#include "choose_number.hpp"

ChooseNumber::ChooseNumber() 
  : user_name_("")
  , max_value_(100)
  , target_value_(GetRandomValue())
  , attempts_count_(0)
  , scores_table_()
  , just_show_table_(false) {}

void ChooseNumber::CheckIncomingParameters(int argc, char **argv)  {
  // В расчет берем только первый параметр
  just_show_table_ = false;
  if (argc >= 2) {
    if (std::string(argv[1]) == "-max") {
      int parameter_value = 0;
      if (argc < 3) {
        std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;    
      } else {
        SetMaxValue(std::stoi(argv[2]));
      }
    } else if (std::string(argv[1]) == "-table") {
      ShowTable();
      just_show_table_ = true;
    } else if (std::string(argv[1]) == "-level") {
      const int level = std::stoi(argv[2]);
      switch(std::stoi(argv[2])) {
        case 1: 
          SetMaxValue(10); 
          break;
        case 2: 
          SetMaxValue(50); 
          break;
        case 3: 
          SetMaxValue(100); 
          break;
        default:
          std::cerr << "Bad level " << level << " should be in range 1-3. Max value will be applied as default (100)" << std::endl;
      }
    }

    // Выводим оставшиеся входные параметры
    if (argc > 3) {
      std::cout << "You entered a lot of parameters, that parameters will be skipped: " << argc << " ";
      for (size_t i = 3; i < argc; ++i)
        std::cout << argv[i] << " ";
      std::cout << std::endl;
    }
  }
}

int ChooseNumber::GetRandomValue() const {
  std::srand(std::time(nullptr));
  return std::rand() % max_value_;
}

void ChooseNumber::Process() {
  if (just_show_table_)
    return;

  std::cout << "Hi! Enter your name, please:" << std::endl;
  std::string user_name;
  std::getline(std::cin, user_name);
  std::cout << "Hello, " << user_name << "!" << std::endl;
  SetUserName(std::move(user_name));
  if (!CheckUserGuess()) {
    std::cerr << "Cannot process user guess" << std::endl;
    return;
  }

  if (!ShowHighScoresTable())
    std::cerr << "Cannot add score of " << user_name_ << std::endl;
}

bool ChooseNumber::CheckUserGuess() {
  int current_value = 0;
  std::cout << "Enter your guess (min: 0, max: "<< (max_value_ - 1) << "):" << std::endl;

  do {
    std::cin >> current_value;
    if (!std::cin.good())
      return false;

    ++attempts_count_;

    if (current_value < target_value_) {
      std::cout << "less than" << std::endl;
    }
    else if (current_value > target_value_) {
      std::cout << "greater than " << std::endl;
    }
    else {
      std::cout << "you win! attempts = " << attempts_count_ << std::endl;
      break;
    }
  } while (true);

  return true;
}

bool ChooseNumber::ShowHighScoresTable() {
  if (!AddToTable())
    return false;

  return true;
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

  std::string line;
  while(std::getline(in_file, line)) {
    const auto&& words = SplitString(line);
    if (words.size() < 2) {
      std::cout << "Bad string: " << line << std::endl;
      continue;
    }

    auto [username, high_score] = GetUserInfo(std::move(words));

    auto it = scores_table_.find(username);
    if (it == scores_table_.end())
      scores_table_.emplace(username, high_score);
    else if (it->second > high_score)
      it->second = high_score;
  }

  for (auto& el : scores_table_)
    std::cout << std::setw(20) << std::left << el.first << '\t' << el.second << std::endl;

  return true;
}

std::vector<std::string> ChooseNumber::SplitString(const std::string& str) const {
    std::istringstream ss(str);
    // Создаем итераторы начала и конца потока
    std::istream_iterator<std::string> it_begin(ss);
    std::istream_iterator<std::string> it_end;

    return {it_begin, it_end};

}

std::pair<std::string, int> ChooseNumber::GetUserInfo(const std::vector<std::string>&& info) const {
    std::string username{};
    size_t last_name_pos = info.size() - 1;
    for (auto i = 0; i < last_name_pos; ++i) {
      username += info[i];
      if (i < last_name_pos - 1)
        username += " ";
    }

    auto high_score = std::stoi(info.back());  
  return {username, high_score};
}

void ChooseNumber::SetMaxValue(const int value) {
  max_value_ = value;
  target_value_ = GetRandomValue();
}

void ChooseNumber::SetUserName(std::string name) {
  user_name_ = std::move(name);
}