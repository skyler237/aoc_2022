#include <iostream>
#include "aoc_puzzle.h"
#include "input.h"
#include <range/v3/getlines.hpp>

class Day1Puzzle : public AoCPuzzle
{
 public:
  Day1Puzzle() : AoCPuzzle(input) {
    int current_calories = 0;
    for(const auto& line : input_.getLines()) {
      if (line.empty()) {
        updateCalories(current_calories);
        current_calories = 0;
      }
      else {
        current_calories += std::stoi(line);
      }
    }
    updateCalories(current_calories);
  }

  void updateCalories(int current_calories)
  {
    if (current_calories > first_) {
      third_  = second_;
      second_ = first_;
      first_  = current_calories;
    }
    else if (current_calories > second_) {
      third_  = second_;
      second_ = current_calories;
    }
    else if (current_calories > third_) {
      third_ = current_calories;
    }
  }

  void printPart1Solution() override {
    std::cout << first_ << std::endl;
  }

  void printPart2Solution() override {
    std::cout << first_ + second_ + third_ << std::endl;
  }

  int first_{0};
  int second_{0};
  int third_{0};
};

int main()
{
  TimedScope timer;
  Day1Puzzle puzzle;

//  std::cout << "Part 1:" << std::endl;
//  puzzle.printPart1Solution();

//  std::cout << "Part 2:" << std::endl;
//  puzzle.printPart2Solution();
  return 0;
}
