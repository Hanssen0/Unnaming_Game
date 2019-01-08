cmake_minimum_required(VERSION 3.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(GenerateExportHeader)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
# For shared library
project(Input_library CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Use c++ 11
add_library(CinInput SHARED CinInput.cc)
generate_export_header(CinInput)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(CinInput PRIVATE -Wall -Wextra)
elseif(MSVC)
  target_compile_options(CinInput PRIVATE /W4)
endif()
# More warnnings
