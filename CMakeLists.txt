cmake_minimum_required(VERSION 3.6)

project(epScript)
add_definitions(-DDOCTEST_CONFIG_DISABLE)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp doctest.hpp factorial.cpp)
add_executable(epScript ${SOURCE_FILES})

project(test)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES testmain.cpp doctest.hpp factorial.cpp)
add_executable(epScriptTest ${SOURCE_FILES})
