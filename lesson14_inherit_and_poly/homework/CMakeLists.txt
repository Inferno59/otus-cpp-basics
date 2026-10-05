cmake_minimum_required(VERSION 3.5)

project(statistics
        VERSION 1.0.0
        DESCRIPTION "Homework about statistics"
        LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
