#include <iostream>
#include <set>
#include "aoc_puzzle.h"
#include "input.h"

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    int row = 0;
    for(const auto& line : input_.getLines()) {
      int col = 0;
      for (const auto& c : line) {
        trees_[row][col] = static_cast<uint8_t>(c) - '0';
        viewing_scores_[row][col] = 1;
        ++col;
      }
      ++row;
    }
    
    for (int idx1 = 1; idx1 < kSize_ - 1; ++idx1) {
      uint8_t left_max = trees_[idx1][0];
      uint8_t right_max = trees_[idx1][kSize_-1];
      uint8_t top_max = trees_[0][idx1];
      uint8_t bottom_max = trees_[kSize_-1][idx1];
      
      // History arrays to keep track of when a tree of that size or greater (by index) was last seen
      std::array<uint8_t, 10> left_history = {0,0,0,0,0,0,0,0,0,0};
      std::array<uint8_t, 10> right_history = {0,0,0,0,0,0,0,0,0,0};
      std::array<uint8_t, 10> top_history = {0,0,0,0,0,0,0,0,0,0};
      std::array<uint8_t, 10> bottom_history = {0,0,0,0,0,0,0,0,0,0};
      
      for (int idx2 = 1; idx2 < kSize_ - 1; ++idx2) {
        // Left to right
        int left_val = trees_[idx1][idx2];
        if (left_val > left_max) {
          left_max = left_val;
          tall_trees_.insert({idx1, idx2});
        }
        int& left_score = viewing_scores_[idx1][idx2];
        int left_distance = idx2 - left_history[left_val];
        left_score *= left_distance;
        if (left_score > max_viewing_score_) {
          max_viewing_score_ = left_score;
        }
        for (; left_val >= 0; --left_val) {
          left_history[left_val] = idx2;
        }

        // Right to left
        int right_col = kSize_ - 1 - idx2;
        int right_val = trees_[idx1][right_col];
        if (right_val > right_max) {
          right_max = right_val;
          tall_trees_.insert({idx1, right_col});
        }
        int& right_score = viewing_scores_[idx1][right_col];
        int right_distance = idx2 - right_history[right_val];
        right_score *= right_distance;
        if (right_score > max_viewing_score_) {
          max_viewing_score_ = right_score;
        }
        for (; right_val >= 0; --right_val) {
          right_history[right_val] = idx2;
        }

        // Top to bottom
        int top_val = trees_[idx2][idx1];
        if (top_val > top_max) {
          top_max = top_val;
          tall_trees_.insert({idx2, idx1});
        }
        int& top_score = viewing_scores_[idx2][idx1];
        int top_distance = idx2 - top_history[top_val];
        top_score *= top_distance;
        if (top_score > max_viewing_score_) {
          max_viewing_score_ = top_score;
        }
        for (; top_val >= 0; --top_val) {
          top_history[top_val] = idx2;
        }

        // Bottom to top
        int bottom_row = kSize_ - 1 - idx2;
        int bottom_val = trees_[bottom_row][idx1];
        if (bottom_val > bottom_max) {
          bottom_max = bottom_val;
          tall_trees_.insert({bottom_row, idx1});
        }
        int& bottom_score = viewing_scores_[bottom_row][idx1];
        int bottom_distance = idx2 - bottom_history[bottom_val];
        bottom_score *= bottom_distance;
        if (bottom_score > max_viewing_score_) {
          max_viewing_score_ = bottom_score;
        }
        for (; bottom_val >= 0; --bottom_val) {
          bottom_history[bottom_val] = idx2;
        }
      }
    }
  }

  int getPart1Solution() override {
    
    return tall_trees_.size() + kSize_ * 4 - 4;
  }

  int getPart2Solution() override {
    return max_viewing_score_;
  }
  
 private:
  std::array<std::array<uint8_t, 99>, 99> trees_{};
  std::array<std::array<int, 99>, 99> viewing_scores_{};
  const int kSize_{99};
  std::set<std::tuple<int,int>> tall_trees_;
  int max_viewing_score_{0};
//  std::array<std::array<char, 197>, 197> debug_{};
//  std::array<std::array<uint8_t, 5>, 5> trees_{};
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
  int iters = 1000;
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

// execution time: 595us