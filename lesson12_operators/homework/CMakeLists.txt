cmake_minimum_required(VERSION 3.7.2)
project(containers)

message(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(containers
  main.cpp
)

target_include_directories(containers 
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties (
  containers PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)