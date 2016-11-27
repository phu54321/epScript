#include "../parser/pygen.h"
#include <sstream>
#include <iostream>
#include "doctest.hpp"

TEST_SUITE("Basic parsing");

TEST_CASE("PyGen testing") {
    PyGenerator pgen;

    pgen << 1 << '+' << 1 << std::endl;
            REQUIRE(pgen.str() == "1+1\n");
    pgen.indent();
    pgen << 2 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n");
    pgen.indent();
    pgen << 3 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n        3\n");
    pgen.unindent();
    pgen.unindent();
    pgen << 4 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n        3\n4\n");
}

TEST_SUITE_END();

