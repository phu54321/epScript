//
// Created by phu54321 on 2017-12-10.
//

#pragma once

#include "../parser/parser.h"
#include "../utils.h"
#include "catch.hpp"
#include <stdexcept>
#include <string.h>
#include <vector>

extern bool NO_EPSPY;
extern bool PARSER_DEBUG, MAP_DEBUG;

std::string get_testdata(std::string dataname);
void checkBlock(const std::string &input, const std::string &desiredOutput);
std::string unindentString(const std::string& data);
std::string trim(std::string s);  // Declared from parserUtilites.h

#define check_file(infile, outfile) CHECK(ParseString("test", get_testdata(infile), false) == get_testdata(outfile))
#define check_string(in, out) CHECK(trim(ParseString("test", in, false)) == trim(out))

#define checkBlock(_input, _output) \
    { \
        std::string input(_input), desiredOutput(_output); \
        std::string output = ParseString("test", "function testf() {" + input + "}", false); \
        const char *header = "@EUDFunc\n" \
                "def f_testf():\n"; \
        REQUIRE(strncmp(output.c_str(), header, strlen(header)) == 0); \
        output = unindentString(output.substr(strlen(header))); \
        CHECK(output == desiredOutput); \
    }
