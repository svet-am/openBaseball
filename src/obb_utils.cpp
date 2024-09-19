//obb_utils.h for OpenBaseball
//https://github.com/svet-am/openBaseball
//written by Tony McDowell (svet.am@gmail.com)

#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 * Referenced from https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
 */
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
// Referenced from https://www.linuxquestions.org/questions/programming-9/c-function-to-get-application-path-335442/
std::string getBasePath(char *path[]){
	char abs_path[PATH_MAX];
	char path_save[PATH_MAX];
	char *p;

	//check for Windows path
	#if defined(_WIN32) || defined(_WIN64)
	if(!(p = strrchr(*path, '\\'))){
		
	//check for Linux / UNIX path	
	#elif defined(__linux__)
	if(!(p = strrchr(*path, '\\'))){
	#endif
    
	return getcwd(abs_path, sizeof(abs_path));
  }
  else{
    *p = '\0';
    getcwd(path_save, sizeof(path_save));
    chdir(*path);
    getcwd(abs_path, sizeof(abs_path));
    chdir(path_save);
	
	return abs_path;
  }
  
  
	//Apple implementation of path fetching
	//  #elif defined(__APPLE__) && defined(__MACH__)

	// should never get here
	return NULL;
}