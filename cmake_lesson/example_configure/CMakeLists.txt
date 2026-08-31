cmake_minimum_required(VERSION 3.22)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch vesrsion")
set(PROJECT_VERSION 0.0.0.${PATCH_VERSION})

message(${PROJECT_VERSION})
project(ExampleConfigure VERSION ${PROJECT_VERSION})

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_executable(project_name main.cpp)

set_target_properties (
  project_name PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_include_directories (
  project_name
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
)
