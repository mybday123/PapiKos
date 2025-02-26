cmake_minimum_required(VERSION 3.10)
project(PapiKos)

set(SOURCES src/main.c)
add_executable(papikos ${SOURCES})
target_include_directories(papikos PRIVATE include)
