cmake_minimum_required(VERSION 3.10)
project(PapiKos)

set(SOURCES src/termui.c)
add_executable(papikos "papikos.c" ${SOURCES})
target_include_directories(papikos PRIVATE include)
