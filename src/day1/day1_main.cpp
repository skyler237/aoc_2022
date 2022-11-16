#include <iostream>
#include "aoc_puzzle.h"

class Day1Puzzle : public AoCPuzzle
{
 public:
  void printPart1Solution() override {
    auto lines = input_.getLinesAsRegexTokens(R"(([0-9]{2}) ([0-9]{2}) ([0-9]{2}) ([0-9]{2}))");
    for (const auto& line : lines) {
      std::cout << line.getMatch() << std::endl;
      auto submatches = line.getSubmatches();
      for (int i = 0; i < submatches.size(); i++) {
        std::cout << "  " << i << ": " << line.getSubmatch(i) << std::endl;
      }
    }
  }

  void printPart2Solution() override {

  }
};

int main()
{
  Day1Puzzle puzzle;

  std::cout << "Part 1:" << std::endl;
  puzzle.printPart1Solution();

  std::cout << "Part 2:" << std::endl;
  puzzle.printPart2Solution();
  return 0;
}
