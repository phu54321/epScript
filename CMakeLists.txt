cmake_minimum_required(VERSION 3.6)
project(epScript)

set_source_files_properties(parser/epparser.c PROPERTIES GENERATED TRUE)

add_custom_command(
        OUTPUT ../parser/epparser.cpp ../parser/epparser.h
        DEPENDS parser/epparser.lemon
        COMMAND lemon parser/epparser.lemon
        COMMAND rm -f parser/epparser.cpp && mv parser/epparser.c parser/epparser.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES ../parser/epparser.cpp parser/tokenizer.cpp parser/tokenizer.h parser/tokChars.cpp parser/tokChars.h parser/tokenizerImpl.cpp parser/tokenizerImpl.h parser/tokIndent.cpp parser/tokIndent.h)
set(TEST_SOURCE_FILES test/test_tokenizer.cpp)

add_executable(epScript ${SOURCE_FILES} main.cpp)
add_executable(epScriptTest ${SOURCE_FILES} ${TEST_SOURCE_FILES} test/testmain.cpp)
set_target_properties(epScript PROPERTIES COMPILE_FLAGS "-DDOCTEST_CONFIG_DISABLE")
