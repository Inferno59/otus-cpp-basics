cmake_minimum_required(VERSION 3.15)

project(gtest_lesson)

# Оптимизация: отключаем сборку тестов и примеров самого GoogleTest
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
set(gtest_build_samples OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.18.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  test/vector_test.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  #${CMAKE_CURRENT_SOURCE_DIR}/../../lesson12_operators/homework/
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME}
  PRIVATE
  cxx_std_17
)

# gtest_main автоматически предоставит функцию main() для запуска тестов
target_link_libraries(${PROJECT_NAME} 
  PRIVATE 
  gtest 
  gtest_main
)