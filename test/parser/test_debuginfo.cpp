//
// Created by phu54321 on 2018-01-22.
//

#include "../test_base.hpp"

TEST_CASE("Debug info") {
    MAP_DEBUG = true;
    // Untyped function
    check_string(
            "function x(l) {\n"
                    "    return 0;"
                    "\n}",
            "@EUDTraced\n"
                    "@EUDFunc\n"
                    "def f_x(l):\n"
                    "    EUDReturn(0)\n"
    );

    MAP_DEBUG = false;
}
