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

    // forEach
    check_string(
        "function x() {\n"
                "    const A, B = 1, 1;\n"
                "    foreach (x : A) {\n"
                "    }\n"
                "\n"
                "    var x;  // Check non-duplicate variable\n"
                "\n"
                "    foreach (x, y : B) {\n"
                "        SetDeaths(x, SetTo, y, 0);\n"
                "    }\n"
                "}",

        "@EUDFunc\n"
                "def f_x():\n"
                "    A, B = List2Assignable([1, 1])\n"
                "    for x in A:\n"
                "        pass\n"
                "\n"
                "    x = EUDVariable()\n"
                "    for x_1, y in B:\n"
                "        DoActions(SetDeaths(x_1, SetTo, y, 0))"

    );
}

TEST_CASE("Import parsing") {
            CHECK(ParseString("test", "import a1;", false) == "from _epspy import a1\n");
            CHECK(ParseString("test", "import test.a1;", false) == "from test._epspy import a1\n");
            CHECK(ParseString("test", "import py_a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.py_a1;", false) == "from test import a1\n");
}

TEST_CASE("Other parsing") {
    SECTION("Auxillary") {
        check_string(
        "var a = 1;\n"
                "const b = 2;\n"
                "\n"
                "function x() {\n"
                "    const A = 1;\n"
                "    A.B();  // Should not have f_A prefix\n"
                "    dwread();  // Should have f_ prefix\n"
                "\n"
                "    var a = dwread()[[5]];\n"
                "    a = A[5];\n"
                "    A[a] = 7;\n"
                "}",

        "a = EUDCreateVariables(1)\n"
                "_IGVA(a, lambda: [1])\n"
                "b = _CGFW(lambda: [2], 1)[0]\n"
                "@EUDFunc\n"
                "def f_x():\n"
                "    A = 1\n"
                "    A.B()\n"
                "    f_dwread()\n"
                "    a_1 = EUDVariable()\n"
                "    a_1 << (f_dwread()[5])\n"
                "    a_1 << (A[5])\n"
                "    _ARRW(A, a_1) << (7)\n"
        );
    }

    SECTION("Object methods") {
        check_string(
                "function f(A) {\n"
                        "    const B = EUDByteReader();\n"
                        "    B.seekepd(A);\n"
                        "    A = B.k;\n"
                        "    B.k = 1;\n"
                        "    A, B.k = 3;\n"
                        "}",

                "@EUDFunc\n"
                        "def f_f(A):\n"
                        "    B = EUDByteReader()\n"
                        "    B.seekepd(A)\n"
                        "    A << (B.k)\n"
                        "    _ATTW(B, 'k') << (1)\n"
                        "    _SV([A, _ATTW(B, 'k')], [3])\n"
        );
    }
}


TEST_CASE("Import parsing with NO_EPSPY") {
    NO_EPSPY = true;
            CHECK(ParseString("test", "import a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.a1;", false) == "from test import a1\n");
            CHECK(ParseString("test", "import py_a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.py_a1;", false) == "from test import a1\n");
    NO_EPSPY = false;
}
