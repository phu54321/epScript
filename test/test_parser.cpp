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

    SUBCASE("Error handling") {
                REQUIRE_THROWS_AS(ParseString("{\n5 + 3 * 7\n}"), std::runtime_error);
    }
}

TEST_CASE("Control block parsing") {
    SUBCASE("Logical operator") {
                REQUIRE(ParseString("if(1 == 2 || 2 + 3 == 5 && 7 == 8) 3;") ==
                        "_t1 = Forward()\n"
                        "_t2 = (1 == 2)\n"
                        "_t3 = 2 + 3\n"
                        "_t4 = (_t3 == 5)\n"
                        "_t5 = (7 == 8)\n"
                        "_t6 = [_t4, _t5]\n"
                        "_t7 = EUDOr([_t2, _t6])\n"
                        "EUDJumpIfNot(_t7, _t1)\n"
                        "_t1 << NextTrigger()\n");

    }

    SUBCASE("If blocks") {
                REQUIRE(ParseString("if(1 == 2) 3 + 4; else 5 + 6;") ==
                        "_t1 = Forward()\n"
                        "_t2 = (1 == 2)\n"
                        "EUDJumpIfNot(_t2, _t1)\n"
                        "_t3 = 3 + 4\n"
                        "_t4 = Forward()\n"
                        "EUDJump(_t4)\n"
                        "_t1 << NextTrigger()\n"
                        "_t5 = 5 + 6\n"
                        "_t4 << NextTrigger()\n");

                REQUIRE(ParseString("if(1 == 2) 3; else if(4 == 5) 6; else 7;") ==
                        "_t1 = Forward()\n"
                        "_t2 = (1 == 2)\n"
                        "EUDJumpIfNot(_t2, _t1)\n"
                        "_t3 = Forward()\n"
                        "EUDJump(_t3)\n"
                        "_t1 << NextTrigger()\n"
                        "_t4 = Forward()\n"
                        "_t5 = (4 == 5)\n"
                        "EUDJumpIfNot(_t5, _t4)\n"
                        "_t6 = Forward()\n"
                        "EUDJump(_t6)\n"
                        "_t4 << NextTrigger()\n"
                        "_t6 << NextTrigger()\n"
                        "_t3 << NextTrigger()\n");
    }

    SUBCASE("While blocks") {
                REQUIRE(ParseString("while(1 == 2) 3 + 4;") ==
                        "_t1 = NextTrigger()\n"
                        "_t2 = Forward()\n"
                        "_t3 = (1 == 2)\n"
                        "EUDJumpIfNot(_t3, _t2)\n"
                        "_t4 = 3 + 4\n"
                        "EUDJump(_t1)\n"
                        "_t2 << NextTrigger()\n");

                REQUIRE(ParseString("while(1 == 2) continue;") ==
                        "_t1 = NextTrigger()\n"
                        "_t2 = Forward()\n"
                        "_t3 = (1 == 2)\n"
                        "EUDJumpIfNot(_t3, _t2)\n"
                        "EUDJump(_t1)\n"
                        "EUDJump(_t1)\n"
                        "_t2 << NextTrigger()\n");
    }

}

TEST_SUITE_END();
