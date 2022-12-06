/*
 * @file input_handler.h
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

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>

#include "range/v3/view.hpp"
#include "aoc_utils.h"

#include "regex_tokens.h"

namespace views = ranges::views;

class InputHandler
{
 public:
  InputHandler() = default;

  void loadInput(const std::string& filename);

  std::basic_istringstream<char> getInputStream();

  template<class T>
  std::vector<T> getObjects() {
    std::vector<T> objects;

    std::copy(std::istream_iterator<T>(getInputStream()),
              std::istream_iterator<T>(),
              std::back_inserter(objects));
    return objects;
  }

  ranges::getlines_view getLines();
  
//  auto getLinesView();

  template<class T>
  std::vector<T> getLinesAsObjects() {
    return input_ | views::split('\n') | ranges::to<std::vector<T>>();
  }

  std::vector<RegexTokens> getLinesAsRegexTokens(const std::string& regex_str);

 private:
  std::string input_;
  std::istringstream input_stream_;

  const auto getLinesView();
};

#endif //INPUT_HANDLER_H
