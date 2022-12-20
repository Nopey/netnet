cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(netnet)

add_executable(main "main.cpp" "networkvar.ixx" "networkvar.h" "player.ixx")
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# dependencies
include(cmake/CPM.cmake)

option(BUILD_DOC "[cereal] Build documentation" OFF)
option(BUILD_SANDBOX "[cereal] Build sandbox examples" OFF)
option(SKIP_PERFORMANCE_COMPARISON "[cereal] Skip building performance sandbox comparison (requires boost)" ON)
CPMAddPackage("gh:USCiLab/cereal#v1.3.2")

target_link_libraries(main cereal::cereal)
