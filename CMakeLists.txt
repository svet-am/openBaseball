#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.15)
# setup CMAKE dependencies
include(ExternalProject)

# setup compiler toolchains
set(CMAKE_C_COMPILER "$ENV{CROSS_COMPILE}gcc")
set(CMAKE_CXX_COMPILER "$ENV{CROSS_COMPILE}g++")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# setup version numbers
set(APP_NAME "OpenBaseball")
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

project(${APP_NAME} C CXX)

message(STATUS "Detected Build OS: ${CMAKE_HOST_SYSTEM_NAME}")

# write the version header for the primary application
file(WRITE ${CMAKE_BINARY_DIR}/../include/obb_version.hpp
"#define OBB_NAME \"${APP_NAME}\"\n"
"#define OBB_VERSION_MAJOR \"${VERSION_MAJOR}\"\n"
"#define OBB_VERSION_MINOR \"${VERSION_MINOR}\"\n"
"#define OBB_VERSION_PATCH \"${VERSION_PATCH}\"\n"
)

# add the external dependency for SFML
set(SFML_CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
					-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/../lib/SFML
					-DBUILD_SHARED_LIBS=1
					-DSFML_BUILD_AUDIO=1
					-DSFML_BUILD_GRAPHICS=1
					-DSFML_BUILD_WINDOW=1
					-DSFML_BUILD_NETWORK=1)
ExternalProject_Add(
	extern-sfml
	SOURCE_DIR ${CMAKE_BINARY_DIR}/../modules/SFML
	CMAKE_ARGS ${SFML_CMAKE_ARGS}
)
add_library(obb_sfml SHARED IMPORTED)

# set up the main application build
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Linux")
	add_executable(${APP_NAME} ${CMAKE_BINARY_DIR}/../src/main.cpp)
	message(SEND_ERROR "Linux currently unsupported")
	return()
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Windows")
	add_executable(${APP_NAME} ${CMAKE_BINARY_DIR}/../src/main.cpp)
	#message(SEND_ERROR "MS Windows currently unsupported")
	#return()
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Darwin")
	add_executable(${APP_NAME} MACOSX_BUNDLE ${CMAKE_BINARY_DIR}/../src/main.cpp)
	message(SEND_ERROR "MacOS / Darwin currently unsupported")
	return()
else()
	message(SEND_ERROR "Trapped in undefined build host OS. Aborting")
	return()
endif()

add_dependencies(${APP_NAME} extern-sfml)