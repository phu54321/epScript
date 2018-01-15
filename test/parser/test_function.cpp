//
// Created by phu54321 on 2018-01-16.
//

#include "../test_base.hpp"

TEST_CASE("Function parsing") {
    check_string(
            "function x(l) {}",
            "@EUDFunc\n"
                    "def f_x(l):\n"
                    "    pass\n"
    );
}
