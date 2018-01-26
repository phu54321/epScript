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

    SECTION("Function call") {
        checkBlock(
                "dwread_epd(0);",
                "EUDTraceLog(1)\n"
                        "f_dwread_epd(0)"
        );
    }

    MAP_DEBUG = false;
}
