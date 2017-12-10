//
// Created by phu54321 on 2017-12-10.
//

#include "test_parser.hpp"

TEST_SUITE("Basic Parser tests");

TEST_CASE("test tool test") {
    CHECK(unindentString("    asdf\n    zxcv\n") == "asdf\nzxcv\n");
    checkBlock("", "pass\n");
}

TEST_CASE("Simple expression parsing") {
    SUBCASE("Simple arithmetic") {
        checkBlock("return 1 + 2;", "EUDReturn(1 + 2)\n");
        checkBlock("return 1 * 2;", "EUDReturn(1 * 2)\n");
        checkBlock("return 1 + 2 * 3;", "EUDReturn(1 + 2 * 3)\n");
        checkBlock("return dwread_epd(0);", "EUDReturn(f_dwread_epd(0))\n");
    }

    SUBCASE("Error handling") {
        // Plain expression cannot appear in program-level
                CHECK((ParseString("test", "2;"), getParseErrorNum() > 0));
    }


    SUBCASE("Global variable management") {
        // Variable declaration is allowed
                CHECK(ParseString("test", "var a;", false) == "a = EUDVariable()\n");
        // Cannot assign varable on global scope
                CHECK((ParseString("test", "var b; b = 2;"), getParseErrorNum() > 0));
    }
}

TEST_CASE("Control block parsing") {
    // Logical operator precedence
    checkBlock(
            "if(1 == 2 || 2 + 3 == 5 && 7 == 8) return 3;",

            "if EUDIf()(EUDOr(1 == 2, [2 + 3 == 5, 7 == 8])):\n"
            "    EUDReturn(3)\n"
            "EUDEndIf()\n"
    );

    // If, ElseIf, Else
    checkBlock(
            "if(1 == 2) return 3;\n"
            "else if(4 == 5) return 6;\n"
            "else {\n"
            "    return 7;\n"
            "}",

            "if EUDIf()(1 == 2):\n"
            "    EUDReturn(3)\n"
            "if EUDElseIf()(4 == 5):\n"
            "    EUDReturn(6)\n"
            "if EUDElse()():\n"
            "    EUDReturn(7)\n"
            "EUDEndIf()\n"
    );

    // While
    checkBlock(
            "while(1 == 2) continue;",

            "if EUDWhile()(1 == 2):\n"
            "    EUDContinue()\n"
            "EUDEndWhile()\n"
    );

    check("ctrlstru/ctrlstru_foreach.eps", "ctrlstru/ctrlstru_foreach.py");
}

TEST_CASE("Import parsing") {
            CHECK(ParseString("test", "import a1;", false) == "from _epspy import a1\n");
            CHECK(ParseString("test", "import test.a1;", false) == "from test._epspy import a1\n");
            CHECK(ParseString("test", "import py_a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.py_a1;", false) == "from test import a1\n");
}


TEST_CASE("Other parsing") {
    check("auxtest.eps", "auxtest.py");
    check("method.eps", "method.py");
}


TEST_SUITE_END();
