#include <iostream>
#include <set>
#include "aoc_puzzle.h"
#include "input.h"

int getItemPriority(const char& item) {
  int priority;
  if (item >= 'a') {
    priority = static_cast<int>(item) - 96;
  }
  else {
    priority = static_cast<int>(item) - 38;
  }
  return priority;
}

class Rucksack
{
 public:
  Rucksack(const std::string& items) {
    int compartment_len = items.size() / 2;
    for (int i = 0; i < items.size(); ++i) {
      char item = items[i];
      if (i < compartment_len) {
        compartment1_.insert(item);
      }
      else {
        if (compartment1_.contains(item)) {
          common_item_ = item;
          break;
        }
      }
    }
  }

  int getPriority() const {
    return getItemPriority(common_item_);
  }

 private:
  std::set<char> compartment1_;
  std::set<char> compartment2_;
  char common_item_;
};

class ElfGroup
{
 public:
  ElfGroup(const std::string& elf1, const std::string& elf2, const std::string& elf3) {
    std::set<char> elf1_set{elf1.begin(), elf1.end()};
    std::set<char> elf2_set{elf2.begin(), elf2.end()};
    for (const auto& c : elf3) {
      if (elf1_set.contains(c) && elf2_set.contains(c)) {
        common_item_priority_ = getItemPriority(c);
        break;
      }
    }
  }

  int getPriority() const {
    return common_item_priority_;
  }

 private:
  int common_item_priority_;

};

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    int i = 0;
    std::array<std::string, 3> elf_group;
    for(const auto& line : input_.getLines()) {
      part1_sum_ += Rucksack(line).getPriority();
      elf_group[i % 3] = line;
      if ((i + 1) % 3 == 0) {
        part2_sum_ += ElfGroup(elf_group[0], elf_group[1], elf_group[2]).getPriority();
      }
      ++i;
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

// Average duration: 570us