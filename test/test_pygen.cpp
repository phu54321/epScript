#include "../parser/generator/pygen.h"
#include <sstream>
#include <iostream>
#include "doctest.hpp"

TEST_SUITE("Pygen tests");

TEST_CASE("String output") {
    PyGenerator pgen;

    pgen << 1 << '+' << 1 << std::endl;
            REQUIRE(pgen.str() == "1+1\n");
    pgen.indent();
    pgen << 2 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n");
    pgen.indent();
    pgen << 3 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n        3\n");
    pgen.unindent(true);
    pgen.unindent(true);
    pgen << 4 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n        3\n\n4\n");
}

TEST_SUITE_END();

