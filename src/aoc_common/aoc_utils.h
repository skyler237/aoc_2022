/*
 * @file aoc_utils.h
 *
 * @brief
 * 
 * @author Skyler Tolman
 * Contact stolman@bastiansolutions.com
 *  
 * Created on 11/17/22.
 * 
 * Copyright (c) 2022 Bastian Solutions. All rights reserved.
 */

#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <chrono>
#include <utility>

typedef std::chrono::steady_clock ClockT;
typedef std::chrono::nanoseconds DurationT;
const std::string kTimePrefix = "us";
const double kTimeMultiplier = 1e-3;
typedef std::chrono::time_point<ClockT, DurationT> TimeT;

template<class T>
T sumTuple(std::tuple<T>&& tuple){
  return std::apply([](auto... v) {
    return (v + ...);
  }, tuple );
}

class TimedScope
{
 public:
  explicit TimedScope(std::string  name = "") : start_(ClockT::now()), name_(std::move(name)){ }

  ~TimedScope() {
    auto end = ClockT::now();
    DurationT duration = end - start_;
    if (!name_.empty()) {
      std::cout << "[" << name_ << "] ";
    }
    std::cout << "Time elapsed: " << static_cast<double>(duration.count()) * kTimeMultiplier << kTimePrefix << std::endl;
  }

 private:
  TimeT start_;
  std::string name_;
};

#endif //AOC_UTILS_H
