//
// Created by phu54321 on 2017-12-10.
//

#include "test_base.hpp"

TEST_CASE("test tool test") {
            CHECK(unindentString("    asdf\n    zxcv\n") == "asdf\nzxcv\n");
    checkBlock("", "pass\n");
}

TEST_CASE("Simple expression parsing") {
            SECTION("Simple arithmetic") {
        checkBlock("return 1 + 2;", "EUDReturn(1 + 2)\n");
        checkBlock("return 1 * 2;", "EUDReturn(1 * 2)\n");
        checkBlock("return 1 + 2 * 3;", "EUDReturn(1 + 2 * 3)\n");
        checkBlock("return dwread_epd(0);", "EUDReturn(f_dwread_epd(0))\n");
    }

            SECTION("Error handling") {
        // Plain expression cannot appear in program-level
                CHECK((ParseString("test", "2;"), getParseErrorNum() > 0));
    }


            SECTION("Global variable management") {
        // Variable declaration is allowed
                check_string("var a;", "a = EUDVariable()\n");
        // Cannot assign varable on global scope
                CHECK((ParseString("test", "var b; b = 2;"), getParseErrorNum() > 0));
    }
}
