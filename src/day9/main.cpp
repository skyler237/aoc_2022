#include <iostream>
#include <set>
#include "aoc_puzzle.h"
#include "input.h"

struct Coordinate
{
  int x;
  int y;
  
  Coordinate(int x, int y) : x(x), y(y) {}
  
  void move(int dx, int dy)
  {
    x += dx;
    y += dy;
  }

  bool operator<(const Coordinate& rhs) const
  {
    if (x < rhs.x)
      return true;
    if (rhs.x < x)
      return false;
    return y < rhs.y;
  }
  
  Coordinate operator-(const Coordinate& rhs) const
  {
    return {x - rhs.x, y - rhs.y};
  }
  
  Coordinate operator+(const Coordinate& rhs) const
  {
    return {x + rhs.x, y + rhs.y};
  }
};

class Rope
{
 public:
  explicit Rope(int size) : knots_(size, Coordinate(0, 0)), head_(knots_[0]), tail_(knots_[size-1]) {};
  
  void moveRope(const char& direction, int count) 
  {
    for (int i = 0; i < count; ++i) {
      moveHead(direction);
      updateTail();
    }
  }
  
  int getTailVisitedLocationCount() {
    return tail_visited_locations_.size();
  }
  
  int getFirstVisitedLocationCount() {
    return first_visited_locations_.size();
  }

 private:
  std::set<Coordinate> first_visited_locations_{Coordinate(0,0)};
  std::set<Coordinate> tail_visited_locations_{Coordinate(0,0)};
  std::vector<Coordinate> knots_{10, Coordinate(0, 0)};
  Coordinate& head_;
  Coordinate& tail_;
  
  void moveHead(char direction)
  {
    switch (direction) {
      case 'U': head_.y++; break;
      case 'D': head_.y--; break;
      case 'L': head_.x--; break;
      case 'R': head_.x++; break;
      default:
        std::cout << "Invalid direction " << direction << std::endl;
    }
  }
  
//  ++U++
//  +===+
//  L=T=R
//  +===+
//  ++D++
  
  void updateTail()
  {
    for (auto it = knots_.begin(); it < knots_.end() - 1; it++) {
      const auto head = *it;
      auto& tail = *(it+1);
      auto relative = head - tail;
      if (relative.x > 1) {
        tail.x++;
        if (relative.y > 0) {
          tail.y++;
        }
        else if (relative.y < 0) {
          tail.y--;
        }
      }
      else if (relative.x < -1) {
        tail.x--;
        if (relative.y > 0) {
          tail.y++;
        }
        else if (relative.y < 0) {
          tail.y--;
        }
      }
      else if (relative.y > 1) {
        tail.y++;
        if (relative.x > 0) {
          tail.x++;
        }
        else if (relative.x < 0) {
          tail.x--;
        }
      }
      else if (relative.y < -1) {
        tail.y--;
        if (relative.x > 0) {
          tail.x++;
        }
        else if (relative.x < 0) {
          tail.x--;
        }
      }
    }
    
    first_visited_locations_.insert(knots_[1]);
    tail_visited_locations_.insert(tail_);
  }
};

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input) {
    for(const auto& line : input_.getLines()) {
      std::istringstream ss(line);
      char direction;
      int count;
      ss >> direction >> count;
      rope_.moveRope(direction, count);
    }
  }

  int getPart1Solution() override {
    return rope_.getFirstVisitedLocationCount();
  }

  int getPart2Solution() override {
    return rope_.getTailVisitedLocationCount();
  }
  
 private:
  Rope rope_{10};
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
