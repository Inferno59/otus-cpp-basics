#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <ctime>
#include <map>

class ChooseNumber final {
  public:
    explicit ChooseNumber();
    ~ChooseNumber() = default;

    void Process();
    void SetMaxValue(const int value);
    void SetUserName(std::string name);
    bool ShowTable();
    
  private:
    ChooseNumber(const ChooseNumber&) = delete;
    ChooseNumber(ChooseNumber&&) = delete;

    ChooseNumber& operator=(const ChooseNumber&) = delete;
    ChooseNumber& operator=(ChooseNumber&&) = delete;

    static constexpr std::string_view kHighScoresFilename = "high_scores.txt";
    static constexpr int kMaxValue = 100;

    int GetRandomValue() const;
    void CheckUserGuess();
    bool ShowHighScoresTable();
    bool AddToTable();

    std::string user_name_;
    int max_value_;
    int target_value_;
    int attempts_count_;
    std::map<std::string, int> scores_table_;
};
