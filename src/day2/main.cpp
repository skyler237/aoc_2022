#include <iostream>
#include "aoc_puzzle.h"
#include "input.h"
#include "range/v3/getlines.hpp"

/**
 * Part 1 Scoring:
 * A = Rock
 * B = Paper
 * C = Scissors
 *
 * X = Rock (1)
 * Y = Paper (2)
 * Z = Scissors (3)
 *
 * A X = Tie + 1 = 3 + 1 = 4
 */
static const std::map<std::string, int> kPart1ScoreMap {
    {"A X", 4}, // Tie + 1 = 4
    {"A Y", 8}, // Win + 2 = 8
    {"A Z", 3}, // Loss + 3 = 3
    {"B X", 1}, // Loss + 1 = 1
    {"B Y", 5}, // Tie + 2 = 5
    {"B Z", 9}, // Win + 3 = 9
    {"C X", 7}, // Win + 1 = 7
    {"C Y", 2}, // Loss + 2 = 2
    {"C Z", 6}, // Tie + 3 = 6
};

static const std::map<std::string, int> kPart2ScoreMap {
    {"A X", 3}, // Lose + 3 = 3
    {"A Y", 4}, // Tie + 1 = 4
    {"A Z", 8}, // Win + 2 = 8
    {"B X", 1}, // Lose + 1 = 1
    {"B Y", 5}, // Tie + 2 = 5
    {"B Z", 9}, // Win + 3 = 9
    {"C X", 2}, // Lose + 2 = 2
    {"C Y", 6}, // Tie + 3 = 6
    {"C Z", 7}, // Win + 1 = 7
};

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    for(const auto& line : input_.getLines()) {
      part1_sum_ += kPart1ScoreMap.at(line);
      part2_sum_ += kPart2ScoreMap.at(line);
    }
  }

  int getPart1Solution() override {
    return part1_sum_;
  }

  int getPart2Solution() override {
    return part2_sum_;
  }

 private:
  int part1_sum_{0};
  int part2_sum_{0};
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
  int iters = 10000;
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

// Execution time: 141us