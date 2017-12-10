//
// Created by phu54321 on 2017-12-10.
//

#pragma once

#include "../../parser/parser.h"
#include "../../utils.h"
#include "../doctest.hpp"
#include <stdexcept>
#include <string.h>
#include <vector>

extern bool NO_EPSPY;

std::string get_testdata(std::string dataname);
void checkBlock(const std::string &input, const std::string &desiredOutput);
std::string unindentString(const std::string& data);
#define check(infile, outfile) CHECK_EQ(ParseString("test", get_testdata(infile), false), get_testdata(outfile))
