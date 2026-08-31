#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <ctime>

class ChooseNumber final {
  public:
    explicit ChooseNumber(std::string name);

    void Process();

  private:
    static constexpr std::string_view kHighScoresFilename = "high_scores.txt";
    static constexpr int kMaxValue = 100;

    int GetRandomValue() const;
    void CheckUserGuess();
    void ShowHighScoresTable();

    std::string user_name_;
    int target_value_;
    int attempts_count_;
};
