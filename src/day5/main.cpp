#include <iostream>
#include "aoc_puzzle.h"
#include "input.h"
#include <stack>

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    auto lines = input_.getLines();
    bool parsing_crates = true;
    bool first_line = true;
    for (const auto& line : lines) {
      // Check if we are parsing crates or actions
      if (parsing_crates && line.find('[') != std::string::npos) {
        int      crate_idx = 0;
        for (int i = 1; i < line.size(); i += 4) {
          char c = line[i];
          if (first_line) {
            initial_crates_.emplace_back();
          }
          if (c != ' ') {
            initial_crates_[crate_idx].push_front(line[i]);
          }
          ++crate_idx;
        }
        first_line = false;
      }
      else {
        parsing_crates = false;
        if (line[0] == 'm') {
          std::istringstream ss(line);
          std::string        word;
          int                count, src, dest;
          ss >> word >> count >> word >> src >> word >> dest;
          actions_.emplace_back(count, src-1, dest-1);
        }
        else {
          // Do nothing
        }
      }
    }
    getInitialCrates();
  }

  void getInitialCrates()
  {
    crates_.clear();
    for (const auto& crate_stack: initial_crates_) {
      std::stack<char> stack;
      for (const auto& crate: crate_stack) {
        stack.push(crate);
      }
      crates_.push_back(stack);
    }
  }

  void moveCrate(std::stack<char>& src, std::stack<char>& dest) {
    assert(!src.empty());
    dest.push(src.top());
    src.pop();
  }

  void moveCrates(int count, int src, int dest) {
    for (int i = 0; i < count; ++i) {
      moveCrate(crates_[src], crates_[dest]);
    }
  }

  void moveCratesGrouped(int count, int src, int dest) {
    std::stack<char> tmp_stack;
    for (int i = 0; i < count; ++i) {
      moveCrate(crates_[src], tmp_stack);
    }
    for (int i = 0; i < count; ++i) {
      moveCrate(tmp_stack, crates_[dest]);
    }
  }

  int getPart1Solution() override {
    for (const auto& [count, src, dest] : actions_) {
      moveCrates(count, src, dest);
    }
//    for(const auto& crate : crates_ | views::transform([](const auto& stack){return stack.top();})) {
//      std::cout << crate;
//    }
//    std::cout << std::endl;
    return 0;
  }

  int getPart2Solution() override {
    getInitialCrates();
    for (const auto& [count, src, dest] : actions_) {
      moveCratesGrouped(count, src, dest);
    }
//    for(const auto& crate : crates_ | views::transform([](const auto& stack){return stack.top();})) {
//      std::cout << crate;
//    }
//    std::cout << std::endl;
    return 0;
  }

 private:
  std::vector<std::deque<char>> initial_crates_;
  std::vector<std::stack<char>> crates_;
  std::vector<std::tuple<int, int, int>> actions_;
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

// Execution time: 269us