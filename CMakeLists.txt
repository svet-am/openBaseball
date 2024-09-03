#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.15)
project(open_baseball C CXX)
# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# setup compiler toolchains
set(CMAKE_C_COMPILER "$ENV{CROSS_COMPILE}gcc")
set(CMAKE_CXX_COMPILER "$ENV{CROSS_COMPILE}g++")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# write the version header for the primary application
file(WRITE ${CMAKE_BINARY_DIR}/../include/obb_version.hpp
"#define OBB_VERSION_MAJOR \"${VERSION_MAJOR}\"\n"
"#define OBB_VERSION_MINOR \"${VERSION_MINOR}\"\n"
"#define OBB_VERSION_PATCH \"${VERSION_PATCH}\"\n"
)
