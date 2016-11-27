#include "../parser/tokenAdapter.h"
#include "doctest.hpp"

TEST_SUITE("Parser tests");

TEST_CASE("Simple expression parsing") {
    SUBCASE("Simple arithmetic") {
                REQUIRE(ParseString("15 + 3;") == "_t1 = 15 + 3\n");
                REQUIRE(ParseString("15 - 3;") == "_t1 = 15 - 3\n");
                REQUIRE(ParseString("15 * 3;") == "_t1 = 15 * 3\n");
                REQUIRE(ParseString("15 / 3;") == "_t1 = 15 // 3\n");
                REQUIRE(ParseString("15 % 3;") == "_t1 = 15 % 3\n");
    }
    SUBCASE("Operator precedence") {
                REQUIRE(ParseString("5 + 3 * 7;") ==
                        "_t1 = 3 * 7\n"
                        "_t2 = 5 + _t1\n");
    }

    SUBCASE("Block parsing") {
                REQUIRE(ParseString("{ 1 + 2; 3 + 4; }") ==
                        "_t1 = 1 + 2\n"
                        "_t2 = 3 + 4\n");
    }


    SUBCASE("Logical operator") {
                REQUIRE(ParseString("1 == 2 || 2 + 3 == 5 && 7 == 8") ==
                        "_t1 = (1 == 2)\n"
                        "_t2 = 2 + 3\n"
                        "_t3 = (_t2 == 5)\n"
                        "_t4 = (7 == 8)\n"
                        "_t5 = [_t3, _t4]\n"
                        "_t6 = EUDOr([_t1, _t5])\n"
        );
    }
}
