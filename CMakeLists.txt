cmake_minimum_required(VERSION 3.5)

project(tictactoe)

add_executable(tictactoe main.cpp)
set_target_properties(tictactoe PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

