//obb_utils.h for OpenBaseball
//https://github.com/svet-am/openBaseball
//written by Tony McDowell (svet.am@gmail.com)
/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 * Referenced from https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
 */
#include <cstddef>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
	#include <windows.h>
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
	#include <limits.h>
	#include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
    #endif
#else
    #define PLATFORM_NAME NULL
#endif

// Return a name of platform, if determined, otherwise - an empty string
std::string getexepath()
{
  char result[ MAX_PATH ];
  #if defined(_WIN32) || defined(_WIN64)
  return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
  #elif defined(__linux__)
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
  #elif defined(__APPLE__) && defined(__MACH__)
  #endif
  
}