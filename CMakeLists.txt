cmake_minimum_required(VERSION 3.30)
project("brew-tools")
include(cmake-libs/all)

find_package(Boost 1.87.0 REQUIRED COMPONENTS process)

build(
  SHARED_LIBRARY homebrewtools
)

build(
  BINARY brew-link-files
  LIBRARIES homebrewtools
  INSTALL_TARGET
)

build(
  BINARY brew-link-apps
  LIBRARIES homebrewtools
  INSTALL_TARGET
)

build(
  BINARY brew-fix-app
  LIBRARIES Boost::process
  INSTALL_TARGET
)
