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
                        "    EUDTraceLog('<test>:f_x:2')\n"
                        "    EUDTracePop()\n"
                        "    EUDReturn(0)\n"
                        "    EUDTraceLog('<test>:f_x:3')\n"
                        "    EUDTracePop()\n"
        );
    }
    MAP_DEBUG = false;
}
