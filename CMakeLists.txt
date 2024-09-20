cmake_minimum_required(VERSION 3.30)
project("brew-tools")

set(CMAKE_CXX_STANDARD 17)

include(global.cmake)

if(APPLE)
  set(CMAKE_INSTALL_RPATH "@loader_path/../lib;@loader_path")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")
endif()

add_subdirectory(libhomebrewtools)
add_subdirectory(brew-link-files)
add_subdirectory(brew-link-apps)

include(GNUInstallDirs)
install(
    TARGETS     homebrewtools brew-link-files brew-link-apps
    INCLUDES    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/homebrewTools"
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
)
