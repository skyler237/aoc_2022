/*
 * @file input_handler.cpp
 *
 * @brief
 * 
 * @author Skyler Tolman
 * Contact stolman@bastiansolutions.com
 *  
 * Created on 11/4/22.
 * 
 * Copyright (c) 2022 Bastian Solutions. All rights reserved.
 */

#include <string>
#include <iostream>
#include "input_handler.h"

void InputHandler::loadInput(const std::string& filename)
{
  input_file_.open(filename);
  if (!input_file_) {
    std::cerr << "Error opening file: " << filename << std::endl;
  }
  else {
    std::cout << "Getting input from " << filename << std::endl;
  }
}

std::vector<std::string> InputHandler::getLines()
{
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_file_, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::vector<RegexTokens> InputHandler::getLinesAsRegexTokens(const std::string& regex_str)
{
  std::vector<RegexTokens> regex_lines;
  std::string line;
  while (std::getline(input_file_, line)) {
    std::istringstream ss;
    RegexTokens tokens(regex_str, line);
    regex_lines.push_back(tokens);
  }
  return regex_lines;
}
