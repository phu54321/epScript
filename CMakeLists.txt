cmake_minimum_required(VERSION 3.6)
project(epScript)

set_source_files_properties(parser/epparser.cpp PROPERTIES GENERATED TRUE)

if (WIN32)
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/parser/epparser.cpp ${CMAKE_SOURCE_DIR}/parser/epparser.h
            DEPENDS parser/epparser.lemon
            COMMAND ./lemon2 parser\\epparser.lemon
            COMMAND copy parser\\epparser.c parser\\epparser.cpp
            COMMAND del parser\\epparser.c
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            VERBATIM
    )

else ()
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/parser/epparser.cpp ${CMAKE_SOURCE_DIR}/parser/epparser.h
            DEPENDS parser/epparser.lemon
            COMMAND ./lemon2 parser/epparser.lemon
            COMMAND rm -f parser/epparser.cpp
            COMMAND mv parser/epparser.c parser/epparser.cpp
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            VERBATIM
    )

endif()

# Size optimization at release mode
if (CMAKE_BUILD_TYPE MATCHES "Release")
    message("release mode - size optimized")
endif()

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/parser/epparser.cpp parser/tokenizer/tokenizer.cpp
        parser/tokenizer/tokChars.cpp parser/tokenizer/tokenizerImpl.cpp
        parser/tokenizer/tokIndent.cpp parser/generator/pygen.cpp parser/tokenAdapter.cpp
        parser/reservedWords/condact.cpp parser/generator/eudplibGlobals.cpp scriptDaemon.cpp parser/generator/closure.cpp
        parser/generator/closure.h parser/parser.h parser/parserUtils.cpp parser/parserUtilsTokens.cpp utils.cpp parser/reservedWords/constparser.cpp parser/reservedWords/constparser.h)
set(TEST_SOURCE_FILES test/test_tokenizer.cpp test/test_pygen.cpp test/test_parser.cpp test/test_library.cpp)

add_executable(epScript ${SOURCE_FILES} main.cpp)
set_target_properties(epScript PROPERTIES COMPILE_FLAGS "-DDOCTEST_CONFIG_DISABLE")
target_link_libraries(epScript -static)

add_library(epScriptLib SHARED ${SOURCE_FILES} libmain.cpp)
set_target_properties(epScriptLib PROPERTIES COMPILE_FLAGS "-DDOCTEST_CONFIG_DISABLE")
target_link_libraries(epScriptLib -static)

add_executable(epScriptTest ${SOURCE_FILES} ${TEST_SOURCE_FILES} test/testmain.cpp)
