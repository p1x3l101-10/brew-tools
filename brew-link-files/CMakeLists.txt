include_directories(../libhomebrewtools/include)
include_directories(../include)
add_module(binary brew-link-files)
target_link_libraries(brew-link-files homebrewtools)
