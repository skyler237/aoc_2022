#include <iostream>
#include "aoc_puzzle.h"
#include "input.h"

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {}

  void printPart1Solution() override {
  }

  void printPart2Solution() override {

  }
};

int main()
{
  TimedScope timer;
  Puzzle puzzle;

  std::cout << "Part 1:" << std::endl;
  puzzle.printPart1Solution();

  std::cout << "Part 2:" << std::endl;
  puzzle.printPart2Solution();
  return 0;
}
