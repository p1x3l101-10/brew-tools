include_directories(../libhomebrewtools/include)
include_directories(../include)
add_module(binary brew-link-apps)
target_link_libraries(brew-link-apps homebrewtools)
