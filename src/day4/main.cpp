#include <iostream>
#include "aoc_puzzle.h"
#include "input.h"

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    auto matches = input_.getLinesAsRegexTokens(R"(([0-9]+)-([0-9]+),([0-9]+)-([0-9]+))");
    for (const auto& match : matches) {
      int min1 = std::stoi(match.getSubmatch(0));
      int max1 = std::stoi(match.getSubmatch(1));
      int min2 = std::stoi(match.getSubmatch(2));
      int max2 = std::stoi(match.getSubmatch(3));
      if ((min1 <= min2 && max1 >= max2) ||
          (min2 <= min1 && max2 >= max1)) {
        ++part1_count_;
      }
      if ((min1 >= min2 && min1 <= max2) ||
          (max1 >= min2 && max1 <= max2) ||
          (min2 >= min1 && min2 <= max1) ||
          (max2 >= min1 && max2 <= max1)) {
        ++part2_count_;
      }
    }

  }

  int getPart1Solution() override {
    return part1_count_;
  }

  int getPart2Solution() override {
    return part2_count_;
  }

 private:
  int part1_count_{0};
  int part2_count_{0};
};

void solvePuzzle(int& part1, int& part2) {
  Puzzle puzzle;
  part1 = puzzle.getPart1Solution();
  part2 = puzzle.getPart2Solution();
}

int main()
{
  int part1;
  int part2;
  int iters = 100;
  DurationT total_duration = DurationT(0);
//  TimedScope timer;
  for (int i = 0; i < iters; ++i) {
    auto start = ClockT::now();
    solvePuzzle(part1, part2);
    auto end = ClockT::now();
    auto duration = end - start;
    total_duration += duration;
  }
  double average_duration_us = static_cast<double>(total_duration.count()) / iters * 1e-3;

  std::cout << "Part1: " << part1 << std::endl;
  std::cout << "Part2: " << part2 << std::endl;

  std::cout << "Average duration: " << average_duration_us << "us" << std::endl;
  return 0;
}
