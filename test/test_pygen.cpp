#include "../parser/pygen.h"
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
    pgen.unindent();
    pgen.unindent();
    pgen << 4 << std::endl;
            REQUIRE(pgen.str() == "1+1\n    2\n        3\n\n4\n");
}

TEST_CASE("Closure name definition") {
    PyGenerator pgen;

            REQUIRE(pgen.undefined("HelloWorld") == true);
    pgen.namedef("HelloWorld");
            REQUIRE(pgen.undefined("HelloWorld") == false);
            REQUIRE(pgen.namedef("HelloWorld") == false);

    pgen.indent();
            REQUIRE(pgen.undefined("HelloWorld") == false);
            REQUIRE(pgen.namedef("HelloWorld") == true);  // Hiding global declaration
            REQUIRE(pgen.namedef("x") == true);
    pgen.unindent();
            REQUIRE(pgen.undefined("x") == true);
            REQUIRE(pgen.undefined("HelloWorld") == false);
}

TEST_SUITE_END();

