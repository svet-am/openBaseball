#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.15)

project(open_baseball C CXX)
set(CMAKE_C_COMPILER "$ENV{CROSS_COMPILE}gcc")
set(CMAKE_CXX_COMPILER "$ENV{CROSS_COMPILE}g++")

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

