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

void InputHandler::loadInput(const std::string& input)
{
  input_ = std::string_view(input);
}

std::vector<std::string> InputHandler::getLines()
{
  return input_ | views::split('\n') | ranges::to<std::vector<std::string>>();
}

std::vector<RegexTokens> InputHandler::getLinesAsRegexTokens(const std::string& regex_str)
{
  std::vector<RegexTokens> regex_lines;
  for (const auto& line : getLines()) {
    std::istringstream ss;
    RegexTokens tokens(regex_str, line);
    regex_lines.push_back(tokens);
  }
  return regex_lines;
}

std::basic_istringstream<char> InputHandler::getInputStream()
{
  return std::istringstream(input_);
}
