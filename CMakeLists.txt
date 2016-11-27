cmake_minimum_required(VERSION 3.6)
project(epScript)

set_source_files_properties(parser/epparser.c PROPERTIES GENERATED TRUE)

add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/parser/epparser.cpp
        DEPENDS parser/epparser.lemon
        COMMAND lemon parser/epparser.lemon
        COMMAND rm -f parser/epparser.cpp && mv parser/epparser.c parser/epparser.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/parser/epparser.cpp parser/tokenizer/tokenizer.cpp parser/tokenizer/tokenizer.h parser/tokenizer/tokChars.cpp parser/tokenizer/tokChars.h parser/tokenizer/tokenizerImpl.cpp parser/tokenizer/tokenizerImpl.h parser/tokenizer/tokIndent.cpp parser/tokenizer/tokIndent.h parser/pygen.h parser/pygen.cpp)
set(TEST_SOURCE_FILES test/test_tokenizer.cpp test/test_parser.cpp)

add_executable(epScript ${SOURCE_FILES} main.cpp)
add_executable(epScriptTest ${SOURCE_FILES} ${TEST_SOURCE_FILES} test/testmain.cpp)
set_target_properties(epScript PROPERTIES COMPILE_FLAGS "-DDOCTEST_CONFIG_DISABLE")
