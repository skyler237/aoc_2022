/*
 * @file regex_tokens.cpp
 *
 * @brief
 * 
 * @author Skyler Tolman
 * Contact stolman@bastiansolutions.com
 *  
 * Created on 11/16/22.
 * 
 * Copyright (c) 2022 Bastian Solutions. All rights reserved.
 */

#include "regex_tokens.h"

RegexTokens::RegexTokens(const std::string& regex_str, const std::string& input) : regex_(regex_str), submatches_()
{
  std::smatch match;
  std::regex_match(input, match, regex_);
  match_ = match[0];
  if (match.size() > 1) {
    auto it = match.begin() + 1;
    while (it != match.end()) {
      submatches_.push_back(*it);
      it++;
    }
  }
}

std::string RegexTokens::getSubmatch(int index) const
{
  return submatches_[index];
}

std::string RegexTokens::getMatch() const
{
  return match_;
}

std::vector<std::string> RegexTokens::getSubmatches() const
{
  return submatches_;
}