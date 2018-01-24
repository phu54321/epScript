//
// Created by phu54321 on 2018-01-22.
//

#include "../test_base.hpp"

TEST_CASE("Debug info") {
    MAP_DEBUG = true;
    SECTION("Untyped function") {
        check_string(
                "function x(l) {\n"
                        "    return 0;"
                        "\n}",
                "@EUDFunc\n"
                        "def f_x(l):\n"
                        "    EUDTracePush()\n"
                        "    EUDTraceLog()\n"
                        "    EUDTracePop()\n"
                        "    EUDReturn(0)\n"
                        "    EUDTraceLog()\n"
                        "    EUDTracePop()\n"
        );
    }

    SECTION("If statement") {
        check_string(
                "function x(l) {\n"
                        "    if(1)\n"
                        "    {}\n"
                        "}",

                "@EUDFunc\n"
                        "def f_x(l):\n"
                        "    EUDTracePush()\n"
                        "    EUDTraceLog()\n"  // Line 2
                        "    if EUDIf()(1):\n"
                        "        EUDTraceLog()\n"  // Line 3
                        "        EUDTraceLog()\n"  // Line 4
                        "    EUDEndIf()\n"
                        "    EUDTracePop()\n"
        );
    }

    SECTION("function call statement") {
        check_string(
                "function x(l) {\n"
                        "    dwread_epd(1);\n"
                        "}",

                "@EUDFunc\n"
                        "def f_x(l):\n"
                        "    EUDTracePush()\n"
                        "    EUDTraceLog()\n"  // Line 2
                        "    f_dwread_epd(1)\n"
                        "    EUDTraceLog()\n"  // Line 3
                        "    EUDTracePop()\n"
        );
    }
    MAP_DEBUG = false;
}
