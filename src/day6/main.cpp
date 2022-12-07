#include <iostream>
#include <set>
#include "aoc_puzzle.h"
#include "input.h"

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    int idx = -1;
    for (const auto& x : std::string_view(input) | views::sliding(14)) {
      ++idx;
      
      std::set<char> set{x.front()};
      auto it = x.begin() + 1;
      bool exit_early = false;
      for ( ; it <= x.begin() + 4; ++it) {
        if (set.contains(*it)) {
          exit_early = true;
          break;
        }
        set.insert(*it);
      }
      
      if (exit_early) continue;
      
      if (part1_solution_ == 0) {
        part1_solution_ = idx + 4;
      }
      
      for ( ; it <= x.begin() + 14; ++it) {
        if (set.contains(*it)) {
          exit_early = true;
          break;
        }
        set.insert(*it);
      }
      
      if (set.size() == 14) {
        part2_solution_ = idx + 14;
        break;
      }
    }
  }

  int getPart1Solution() override {
    return part1_solution_;
  }
  int getPart2Solution() override {
    return part2_solution_;
  }
  
 private:
  int part1_solution_{0};
  int part2_solution_{0};
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

// execution time: 373us