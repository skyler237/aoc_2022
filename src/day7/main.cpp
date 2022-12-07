#include <iostream>
#include <set>
#include "aoc_puzzle.h"
#include "input.h"

struct File {
  int size;
};

class Directory
{
 public:  
  Directory(Directory* parent_dir) : parent_dir_(parent_dir) {
    
  };

  bool operator< (const Directory& dir) const
  {
    return (this->files_size_ < dir.files_size_);
  }
  
  void addFile(int size) {
    files_size_ += size;
  }
  
  void addSubdir(const std::string& name) {
    if (dirs_.find(name) == dirs_.end()) {
      dirs_.emplace(std::pair<std::string, Directory>{name, Directory(this)});
    }
  }
  
  Directory* getSubdir(const std::string& name) {
    return &dirs_.at(name);
  }
  
  Directory* getParentDir() {
    return parent_dir_;
  }
  
  int findDirsPart1(int& current_sum, std::set<int>& dir_sizes) const
  {
    int total_size = files_size_;
    for (const auto& [_, dir] : dirs_) {
      total_size += dir.findDirsPart1(current_sum, dir_sizes);
    }
    if (total_size <= 100000) {
      current_sum += total_size;
    }
    dir_sizes.insert(total_size);
    return total_size;
  }

 private:
  Directory* parent_dir_;
  std::map<std::string, Directory> dirs_;
  int files_size_{0};
};

class Puzzle : public AoCPuzzle
{
 public:
  Puzzle() : AoCPuzzle(input), root_(nullptr), cwd_(&root_) {
    for(const auto& line : input_.getLines()) {
      char first_char = line[0];
      if (first_char == '$') {
        handleCommand(line.substr(2));
      }
      else if (first_char == 'd') {
        handleDir(line.substr(4));
      }
      else {
        handleFile(line);
      }
    }
  }

  int getPart1Solution() override {
    int sum = 0;
    current_usage_ = root_.findDirsPart1(sum, dir_sizes_);
    return sum;
  }

  int getPart2Solution() override {
    int memory_remaining = 70000000 - current_usage_;
    int to_delete = 30000000 - memory_remaining;
    for (const auto& size : dir_sizes_) {
      if (size > to_delete) {
        return size;
      }
    }
    return 0;
  }
  
  void handleCommand(const std::string& command_str) {
    std::istringstream ss(command_str);
    std::string command;
    ss >> command;
    if (command[0] == 'c') { // cd commands
      std::string dirname;
      ss >> dirname;
      if (dirname == "..") {
        cwd_ = cwd_->getParentDir();
      }
      else if (dirname == "/") {
        cwd_ = &root_;
      }
      else {
        cwd_ = cwd_->getSubdir(dirname);
      }
    }
  }
  
  void handleDir(const std::string& dirname) {
    cwd_->addSubdir(dirname);
  }
  
  void handleFile(const std::string& file_info) {
    std::istringstream ss(file_info);
    int file_size;
    ss >> file_size;
    cwd_->addFile(file_size);
  }
  
 private:
  Directory root_;
  Directory* cwd_;
  int current_usage_{0};
  std::set<int> dir_sizes_;
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

// Execution time: 321 us