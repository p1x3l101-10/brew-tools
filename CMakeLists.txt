cmake_minimum_required(VERSION 3.16)

project(brew-tools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(brew-tools main.cpp)

include(GNUInstallDirs)
install(TARGETS brew-tools
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
