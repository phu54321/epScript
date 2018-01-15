//
// Created by phu54321 on 2018-01-16.
//

#include "../test_base.hpp"

TEST_CASE("Function parsing") {
    SECTION("Untyped function") {
        check_string(
                "function x(l) {}",
                "@EUDFunc\n"
                        "def f_x(l):\n"
                        "    pass\n"
        );
    }

    SECTION("Typed Function parsing") {
        check_string(
                "function x(a: EUDArray) {}",
                "@EUDTypedFunc([EUDArray])\n"
                        "def f_x(a):\n"
                        "    pass\n"
        );
    }
}

