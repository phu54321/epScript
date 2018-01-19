cmake_minimum_required(VERSION 3.6)
project(epScript)

set(EPSCRIPT_VERSION 1.3.0)
set(EPSCRIPT_SOVERSION 1.3)

if (WIN32)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEAaSE} -s")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
endif()

set_source_files_properties(parser/epparser.cpp PROPERTIES GENERATED TRUE)

if (WIN32)
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/parser/epparser.cpp ${CMAKE_SOURCE_DIR}/parser/epparser.h
            DEPENDS ./lemon2.exe parser/epparser.lemon
            COMMAND ./lemon2 -p -c -l parser\\epparser.lemon
            COMMAND copy parser\\epparser.c parser\\epparser.cpp
            COMMAND del parser\\epparser.c
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            VERBATIM
    )

else ()
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/parser/epparser.cpp ${CMAKE_SOURCE_DIR}/parser/epparser.h
            DEPENDS ./lemon2 parser/epparser.lemon
            COMMAND ./lemon2 parser/epparser.lemon
            COMMAND rm -f parser/epparser.cpp
            COMMAND mv parser/epparser.c parser/epparser.cpp
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            VERBATIM
    )

endif()

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/parser/epparser.cpp parser/tokenizer/tokenizer.cpp
        parser/tokenizer/tokChars.cpp parser/tokenizer/tokenizerImpl.cpp
        parser/generator/pygen.cpp parser/tokenAdapter.cpp
        parser/reservedWords/condact.cpp parser/generator/eudplibGlobals.cpp parser/generator/closure.cpp
        parser/generator/closure.h parser/parser.h parser/parserUtils.cpp parser/parserUtilsTokens.cpp utils.cpp
        parser/reservedWords/constparser.cpp parser/reservedWords/constparser.h parser/utils/subTokenUtils.cpp parser/utils/subTokenUtils.h)

set(TEST_SOURCE_FILES
        test/test_tokenizer.cpp test/test_pygen.cpp test/test_base.cpp test/parser/test_arraydecl.cpp
        test/parser/test_complex.cpp test/parser/test_ctrlstru.cpp
        test/parser/test_globalv.cpp test/parser/test_import.cpp test/parser/test_noepspy.cpp
        test/parser/test_object.cpp test/parser/test_ternary.cpp test/parser/test_pyliteral.cpp
        test/parser/test_expression.cpp test/test_testtool.cpp test/parser/test_function.cpp)

add_definitions(-DVERSION="${EPSCRIPT_VERSION}")

add_executable(epScript ${SOURCE_FILES} main.cpp scriptDaemon.cpp)
add_library(epScriptLib SHARED ${SOURCE_FILES} libmain.cpp)
set_target_properties(epScriptLib  PROPERTIES
        VERSION ${EPSCRIPT_VERSION}
        SOVERSION ${EPSCRIPT_SOVERSION}
)
add_executable(epScriptTest ${SOURCE_FILES} ${TEST_SOURCE_FILES} test/testmain.cpp)
add_executable(epScriptProfile ${SOURCE_FILES} libmain.cpp test/stresstest.cpp)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    message("release mode - static linked")
    if (WIN32)
        target_link_libraries(epScript -static)
        target_link_libraries(epScriptLib -static)
    endif()
endif()
