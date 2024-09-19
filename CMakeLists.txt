cmake_minimum_required(VERSION 3.30)
project("brew-tools")

set(CMAKE_CXX_STANDARD 17)

include(global.cmake)

add_subdirectory(libhomebrewtools)
add_subdirectory(brew-link-files)
