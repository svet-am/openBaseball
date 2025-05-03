#CMake for OpenBaseball
#https://github.com/svet-am/openBaseball
#written by Tony McDowell (svet.am@gmail.com)
cmake_minimum_required(VERSION 3.25)
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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/bin)

## Add wxWidget to project
set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)
set(wxUSE_STL OFF)
set(wxUSE_REGEX builtin)
set(wxUSE_ZLIB builtin)
set(wxUSE_EXPAT builtin)
set(wxUSE_LIBJPEG builtin)
set(wxUSE_LIBPNG builtin)
set(wxUSE_LIBTIFF builtin)
set(wxUSE_NANOSVG builtin)
set(wxUSE_LIBLZMA builtin)
message(STATUS "Fetching sources for: WXWIDGETS")
FetchContent_Declare(
	wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.2.7.1
	)
FetchContent_GetProperties(wxWidgets)
FetchContent_MakeAvailable(wxWidgets)

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
target_include_directories(${APP_NAME} PRIVATE  ${wxWidgets_SOURCE_DIR}/include)
target_link_libraries(${APP_NAME} PRIVATE obb-utils)

#wxWIDGETS libraries
target_link_libraries(${APP_NAME} PRIVATE wxbase wxcore)
# Valid wxWIDGETS Library Dependency Names
# wxregex # wxzlib # wxexpat # wxjpeg # wxpng # wxtiff # wxbase # wxnet # wxcore # wxadv # wxaui # wxhtml # wxpropgrid # wxribbon # wxxml # wxrichtext # wxwebview
# wxscintilla # wxstc # wxxrc # wxmedia # wxgl # wxqa # wxrc

# set OS-specific dependencies
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Linux")
	message(STATUS "Copying wxWidgtes platform-specific data for ${CMAKE_HOST_SYSTEM_NAME}")
	target_link_libraries(${APP_NAME} PUBLIC "-lGL")
	target_link_libraries(${APP_NAME} PUBLIC "-lGLU")
	
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL  "Windows")
	message(STATUS "Copying wxWidgtes platform-specific data for ${CMAKE_HOST_SYSTEM_NAME}")
	file(COPY ${CMAKE_BINARY_DIR}/_deps/wxwidgets-src/include/wx/msw/setup.h DESTINATION ${CMAKE_BINARY_DIR}/_deps/wxwidgets-src/include/wx)
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

# write the version header for the primary application
message(STATUS "Installing VERSION HEADER resources")
file(WRITE ${CMAKE_BINARY_DIR}/../src/obb_version.hpp
"#define OBB_NAME \"${APP_NAME}\"\n"
"#define OBB_VERSION_MAJOR \"${VERSION_MAJOR}\"\n"
"#define OBB_VERSION_MINOR \"${VERSION_MINOR}\"\n"
"#define OBB_VERSION_PATCH \"${VERSION_PATCH}\"\n"
"const char* OBB_NAME_VER = OBB_NAME \" \" OBB_VERSION_MAJOR \".\" OBB_VERSION_MINOR \".\" OBB_VERSION_PATCH ;\n"
)

message(STATUS "Installing IMAGE resources")
file(COPY ${CMAKE_BINARY_DIR}/../res/img/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/img/)

message(STATUS "Installing SOUND resources")
