cmake_minimum_required(VERSION 3.10)
project(PapiKos)

if(MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /ZI")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
endif()

set(SOURCES src/termui.c "src/login.c")
add_executable(papikos "papikos.c" ${SOURCES})
target_include_directories(papikos PRIVATE include)
