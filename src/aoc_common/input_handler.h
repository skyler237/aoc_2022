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
#include <ranges>
#include <sstream>

#include "regex_tokens.h"

namespace views = std::ranges::views;

class InputHandler
{
 public:
  InputHandler() = default;

  void loadInput(const std::string& filename);

  template<class T>
  std::vector<T> getObjects() {
    std::vector<T> objects;

    std::copy(std::istream_iterator<T>(input_file_),
              std::istream_iterator<T>(),
              std::back_inserter(objects));
    return objects;
  }

  std::vector<std::string> getLines();

  template<class T>
  std::vector<T> getLinesAsObjects() {
    std::vector<T> objects;
    std::string line;
    while (std::getline(input_file_, line)) {
      std::istringstream ss;
      T object;
      ss >> object;
      objects.push_back(object);
    }
    return objects;
  }

  std::vector<RegexTokens> getLinesAsRegexTokens(const std::string& regex_str);

 private:
  std::ifstream input_file_;

};

#endif //INPUT_HANDLER_H
