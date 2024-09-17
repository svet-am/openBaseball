#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.30)
# setup CMAKE dependencies
include(FetchContent)

# setup version numbers
set(APP_NAME "OpenBaseball")
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

project(${APP_NAME} C CXX)

# setup compiler toolchains
#set(CMAKE_C_COMPILER "$ENV{CROSS_COMPILE}gcc")
#set(CMAKE_CXX_COMPILER "$ENV{CROSS_COMPILE}g++")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Detected Build OS: ${CMAKE_HOST_SYSTEM_NAME}")

# write the version header for the primary application
file(WRITE ${CMAKE_BINARY_DIR}/../src/obb_version.hpp
"#define OBB_NAME \"${APP_NAME}\"\n"
"#define OBB_VERSION_MAJOR \"${VERSION_MAJOR}\"\n"
"#define OBB_VERSION_MINOR \"${VERSION_MINOR}\"\n"
"#define OBB_VERSION_PATCH \"${VERSION_PATCH}\"\n"
"const char* OBB_NAME_VER = OBB_NAME \" \" OBB_VERSION_MAJOR \".\" OBB_VERSION_MINOR \".\" OBB_VERSION_PATCH ;\n"
)

# add the external dependency for SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build SFML shared libraries" ON)
option(SFML_BUILD_NETWORK "Build SFML network support" ON)
option(SFML_BUILD_AUDIO "Build SFML audio support" ON)
option(SFML_BUILD_GRAPHICS "Build SFML graphics support" ON)
option(SFML_BUILD_WINDOW "Build SFML window management support" ON)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
	SYSTEM)
FetchContent_MakeAvailable(SFML)

# add the obb-utils library
# obb_utils is special housekeeping functions for obb-utils
add_library(obb-utils SHARED)
target_sources(obb-utils PRIVATE
				${CMAKE_BINARY_DIR}/../src/obb_utils.cpp
)
target_sources(obb-utils PUBLIC
				${CMAKE_BINARY_DIR}/../src/obb_utils.hpp
)

# set up the main application build
add_executable(${APP_NAME} ${CMAKE_BINARY_DIR}/../src/main.cpp)
target_compile_features(${APP_NAME} PRIVATE cxx_std_17)
target_include_directories(${APP_NAME} PRIVATE  ${CMAKE_BINARY_DIR}/_deps/sfml-src/include)
target_link_libraries(${APP_NAME} PRIVATE sfml-system)
target_link_libraries(${APP_NAME} PRIVATE sfml-window)
target_link_libraries(${APP_NAME} PRIVATE sfml-graphics)
target_link_libraries(${APP_NAME} PRIVATE obb-utils)

# set OS-specific dependencies
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Linux")
	message(SEND_ERROR "Linux currently unsupported")
	return()

elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Windows")
	target_link_libraries(${APP_NAME} PUBLIC "-lopengl32")
	target_link_libraries(${APP_NAME} PUBLIC "-lwinmm")
	target_link_libraries(${APP_NAME} PUBLIC "-lgdi32")

elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Darwin")
	message(SEND_ERROR "MacOS / Darwin currently unsupported")
	return()

else()
	message(SEND_ERROR "Trapped in undefined build host OS. Aborting")
	return()

endif()

# copy resources into the install directory
message(STATUS "Installing IMAGE resources")
file(COPY ${CMAKE_BINARY_DIR}/../res/img/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/img/)