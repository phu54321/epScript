//
// Created by phu54321 on 2018-01-22.
//

#include "../test_base.hpp"

TEST_CASE("Debug info") {
    MAP_DEBUG = true;

    SECTION("Untyped function") {
        check_string(
                "function x(l) {\n"
                        "\n}",
                "@EUDTraced\n"
                        "@EUDFunc\n"
                        "def f_x(l):\n"
                        "    pass"
        );
    }

    SECTION("Statements") {

        SECTION("Function call") {
            checkBlock(
                    "dwread_epd(0);",
                    "EUDTraceLog(1)\n"
                            "f_dwread_epd(0)"
            );
        }

        SECTION("Constant declaration") {
            checkBlock(
                    "const A = 1;",
                    "EUDTraceLog(1)\n"
                            "A = 1"
            );
        }
        SECTION("Variable declaration") {
            checkBlock(
                    "var A;",
                    "A = EUDVariable()"  // Pure variable declaration is not traced.
            );

            checkBlock(  // Variable declaration with assignments.
                    "var A = 1;",
                    "EUDTraceLog(1)\n"
                            "A = EUDVariable()\n"
                            "A << (1)\n"
            );
        }

    }

    SECTION("Control blocks") {
        SECTION("For") {
            checkBlock(
                    "for(const i = EUDArray() ; i.empty() ; dwread_epd(i)) {}",

                    "EUDTraceLog(1)\n"
                            "i = EUDArray()\n"
                            "_t1 = EUDWhile()\n"
                            "EUDTraceLog(1)\n"
                            "if _t1(i.empty()):\n"
                            "    def _t2():\n"
                            "        EUDTraceLog(1)\n"
                            "        f_dwread_epd(i)\n"
                            "    EUDSetContinuePoint()\n"
                            "    _t2()\n"
                            "EUDEndWhile()\n"
            );
        }

        SECTION("While") {
            checkBlock(
                    "while(1) {\n"
                            "    const x = 1;\n"
                            "}",

                    "_t1 = EUDWhile()\n"
                            "EUDTraceLog(1)\n"
                            "if _t1(1):\n"
                            "    EUDTraceLog(2)\n"
                            "    x = 1\n"
                            "EUDEndWhile()\n"
            );
        }

        SECTION("While") {
            checkBlock(
                    "while(1) {\n"
                            "    const x = 1;\n"
                            "}",

                    "_t1 = EUDWhile()\n"
                            "EUDTraceLog(1)\n"
                            "if _t1(1):\n"
                            "    EUDTraceLog(2)\n"
                            "    x = 1\n"
                            "EUDEndWhile()\n"
            );
        }
    }

    MAP_DEBUG = false;
}
