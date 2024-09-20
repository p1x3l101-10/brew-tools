cmake_minimum_required(VERSION 3.30)
project("brew-tools")

set(CMAKE_CXX_STANDARD 17)

include(global.cmake)

add_subdirectory(libhomebrewtools)
add_subdirectory(brew-link-files)

include(GNUInstallDirs)
list( APPEND CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_LIBDIR} )
install(
    TARGETS     homebrewtools brew-link-files
    INCLUDES    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Add the stupid script I haven't converted yet
install(
    PROGRAMS    brew-link-apps.bash
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    RENAME      brew-link-apps
)
