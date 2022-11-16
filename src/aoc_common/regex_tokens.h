/*
 * @file regex_tokens.h
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

#ifndef REGEX_TOKENS_H
#define REGEX_TOKENS_H

#include <regex>
#include <utility>

class RegexTokens
{
 public:
  explicit RegexTokens(const std::string& regex_str, const std::string& input);

  std::string getMatch() const;

  std::string getSubmatch(int index) const;

  std::vector<std::string> getSubmatches() const;

 private:
  const std::regex regex_;
  std::string match_;
  std::vector<std::string> submatches_;
};

#endif //REGEX_TOKENS_H
