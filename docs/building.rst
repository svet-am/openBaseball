===============================
INTRODUCTION
===============================
OpenBaseball is buildable on multiple targets, including:
* Microsoft Windows (10+)
* Linux (Ubuntu, Debian, and similar)
* Apple MacOS X (for future - versions and requirements TBD)

===============================
DEPENDENCIES
===============================

===============================
BUILDING FOR MICROSOFT WINDOWS
===============================
Builds on Microsoft Windows depend on the following additional tools:
1) MSYS2

SETTING UP MSYS2

Set up MSYS2 build dependencies
1) Update the MSYS2 environment
``$ pacman -Syu``

2) Add baseline build dependencies
``$ pacman -S development gcc vim cmake``

Important! When building for MS Windows, be sure to install the UCRT64 version of all tools and libraries

