cmake_minimum_required(VERSION 3.30)
project("brew-tools")

include(global.cmake)

add_subdirectory(libhomebrewtools)

include_directories(libhomebrewtools/include)
add_module(binary test)
target_link_libraries(test homebrewtools)
