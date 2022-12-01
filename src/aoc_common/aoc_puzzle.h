/*
 * @file ao_c_puzzle.h
 *
 * @brief
 * 
 * @author Skyler Tolman
 * Contact stolman@bastiansolutions.com
 *  
 * Created on 11/11/22.
 * 
 * Copyright (c) 2022 Bastian Solutions. All rights reserved.
 */

#ifndef AOC_PUZZLE_H
#define AOC_PUZZLE_H

#include <string>
#include <iostream>
#include "input_handler.h"

class AoCPuzzle
{
 public:
  explicit AoCPuzzle(const std::string& input);

  virtual void printPart1Solution() {
    std::cout << "Part 1 not implemented yet..." << std::endl;
  }

  virtual void printPart2Solution() {
    std::cout << "Part 2 not implemented yet..." << std::endl;
  }

 protected:
  InputHandler input_;

};

#endif //AOC_PUZZLE_H
