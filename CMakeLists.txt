cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
add_compile_options(-std=c++1z)
project(CCAGE VERSION 0.9 LANGUAGES CXX)
add_definitions(-DCAGE_PREFIX)
SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${SDL2_INCLUDE_DIR})

set (COMMON_LIBS
      SDL2 SDL2_mixer SDL2_image)

add_subdirectory(src/)
add_subdirectory(samples/)
