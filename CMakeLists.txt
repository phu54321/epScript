cmake_minimum_required(VERSION 3.6)
project(epScript)

find_package(BISON)
find_package(FLEX)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES doctest.hpp factorial.cpp)

add_executable(epScript ${SOURCE_FILES} main.cpp)
add_executable(epScriptTest ${SOURCE_FILES} testmain.cpp)
set_target_properties(epScript PROPERTIES COMPILE_FLAGS "-DDOCTEST_CONFIG_DISABLE")
