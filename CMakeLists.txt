cmake_minimum_required(VERSION 3.0)
project(cods)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(platform)
include(target)

#add_subdirectory(examples)

include(CTest)
enable_testing()
add_subdirectory(tests)

message(STATUS "--------------------------------------------------")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "--------------------------------------------------")
