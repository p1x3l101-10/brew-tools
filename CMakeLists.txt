cmake_minimum_required(VERSION 3.30)
project("brew-tools")
include(cmake-libs/all)

build(
  STATIC_LIBRARY homebrewtools
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
