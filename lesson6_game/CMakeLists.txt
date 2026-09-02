cmake_minimum_required(VERSION 3.5)

project(choose_number)

add_executable(
	game_choose_number
	main.cpp
	choose_number.cpp
)

set_target_properties (
  game_choose_number PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
