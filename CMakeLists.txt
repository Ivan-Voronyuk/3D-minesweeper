cmake_minimum_required(VERSION 3.2)

project(minesweeper)

option(BUILD_FLTK_TEST "build FLTK hello_world" ON)

set(FLTK_BUILD_TESTS OFF)
set(FLTK_BUILD_FLUID OFF)
set(FLTK_BUILD_SHARED_LIBS ON)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  set(BUILD_FLTK_TEST ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT TARGET fltk)
  add_subdirectory(thirdparty/fltk)
endif()

if(BUILD_FLTK_TEST)
  add_executable(fltk_hello_world test/fltk_hello_world.cpp)
  target_link_libraries(fltk_hello_world PUBLIC fltk)
  target_include_directories(fltk_hello_world PUBLIC)
endif()

add_library(Graph_lib src/Graph_lib/GUI.cpp src/Graph_lib/Graph.cpp
                      src/Graph_lib/Window.cpp)
target_link_libraries(Graph_lib PUBLIC fltk)
