#include "../parser/tokenAdapter.h"
#include "doctest.hpp"

TEST_SUITE("Parser tests");

TEST_CASE("Simple expression parsing") {
    SUBCASE("Simple arithmetic") {
                REQUIRE(ParseString("15 + 3") == "_t1 = 15 + 3\n");
                REQUIRE(ParseString("15 - 3") == "_t1 = 15 - 3\n");
                REQUIRE(ParseString("15 * 3") == "_t1 = 15 * 3\n");
                REQUIRE(ParseString("15 / 3") == "_t1 = 15 // 3\n");
                REQUIRE(ParseString("15 % 3") == "_t1 = 15 % 3\n");
    }
    SUBCASE("Operator precedence") {
                REQUIRE(ParseString("5 + 3 * 7") ==
                        "_t1 = 3 * 7\n"
                        "_t2 = 5 + _t1\n");
    }
}
