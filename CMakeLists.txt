#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.30)
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
file(WRITE ${CMAKE_BINARY_DIR}/../src/obb_version.hpp
"#define OBB_NAME \"${APP_NAME}\"\n"
"#define OBB_VERSION_MAJOR \"${VERSION_MAJOR}\"\n"
"#define OBB_VERSION_MINOR \"${VERSION_MINOR}\"\n"
"#define OBB_VERSION_PATCH \"${VERSION_PATCH}\"\n"
)

# add the external dependency for SFML
set(SFML_CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
					-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
					-DBUILD_SHARED_LIBS=0
					-DSFML_USE_STATIC_STD_LIBS=1
					-DSFML_BUILD_EXAMPLES=0
					-DSFML_BUILD_AUDIO=0
					-DSFML_BUILD_GRAPHICS=1
					-DSFML_BUILD_WINDOW=1
					-DSFML_BUILD_NETWORK=0
)
ExternalProject_Add(
	extern-sfml
	SOURCE_DIR ${CMAKE_BINARY_DIR}/../modules/SFML
	CMAKE_ARGS ${SFML_CMAKE_ARGS}
)
 
# set up the main application build
add_executable(${APP_NAME} ${CMAKE_BINARY_DIR}/../src/main.cpp)
add_dependencies(${APP_NAME} extern-sfml)
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/lib)

target_include_directories(${APP_NAME} PUBLIC ${CMAKE_BINARY_DIR}/../modules/SFML/include)
target_link_directories(${APP_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(${APP_NAME} PUBLIC "-lsfml-system-s")
target_link_libraries(${APP_NAME} PUBLIC "-lsfml-main")
target_link_libraries(${APP_NAME} PUBLIC "-lsfml-window-s")
target_link_libraries(${APP_NAME} PUBLIC "-lsfml-graphics-s")
target_link_libraries(${APP_NAME} PUBLIC "-lopengl32")
target_link_libraries(${APP_NAME} PUBLIC "-lwinmm")
target_link_libraries(${APP_NAME} PUBLIC "-lgdi32")
	
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Linux")
	message(SEND_ERROR "Linux currently unsupported")
	return()
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Windows")


	#message(SEND_ERROR "MS Windows currently unsupported")
	#return()
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Darwin")
	message(SEND_ERROR "MacOS / Darwin currently unsupported")
	return()
else()
	message(SEND_ERROR "Trapped in undefined build host OS. Aborting")
	return()
endif()
