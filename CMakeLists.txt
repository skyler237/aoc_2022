cmake_minimum_required(VERSION 3.23)
project(aoc_2022)

set(CMAKE_CXX_STANDARD 23)

set(COMMON
        src/aoc_common/input_handler.cpp src/aoc_common/aoc_puzzle.cpp src/aoc_common/aoc_puzzle.h src/aoc_common/regex_tokens.cpp)

include_directories(src/aoc_common)
include_directories(src/range-v3/include)

add_executable(day1 src/day1/day1_main.cpp ${COMMON})
add_executable(day2 src/day2/main.cpp ${COMMON})
add_executable(day3 src/day3/main.cpp ${COMMON})
add_executable(day4 src/day4/main.cpp ${COMMON})
add_executable(day5 src/day5/main.cpp ${COMMON})
add_executable(day6 src/day6/main.cpp ${COMMON})
add_executable(day7 src/day7/main.cpp ${COMMON})
add_executable(day8 src/day8/main.cpp ${COMMON})
add_executable(day9 src/day9/main.cpp ${COMMON})
add_executable(day10 src/day10/main.cpp ${COMMON})
add_executable(day11 src/day11/main.cpp ${COMMON})
add_executable(day12 src/day12/main.cpp ${COMMON})
add_executable(day13 src/day13/main.cpp ${COMMON})
add_executable(day14 src/day14/main.cpp ${COMMON})
add_executable(day15 src/day15/main.cpp ${COMMON})
add_executable(day16 src/day16/main.cpp ${COMMON})
add_executable(day17 src/day17/main.cpp ${COMMON})
add_executable(day18 src/day18/main.cpp ${COMMON})
add_executable(day19 src/day19/main.cpp ${COMMON})
add_executable(day20 src/day20/main.cpp ${COMMON})
add_executable(day21 src/day21/main.cpp ${COMMON})
add_executable(day22 src/day22/main.cpp ${COMMON})
add_executable(day23 src/day23/main.cpp ${COMMON})
add_executable(day24 src/day24/main.cpp ${COMMON})
add_executable(day25 src/day25/main.cpp ${COMMON})
