//
// Created by phu54321 on 2018-01-08.
//

#include "test_base.hpp"

TEST_CASE("Multiple variable") {
    check_string(
            "var a, b = 1, 2;",

            "a, b = EUDCreateVariables(2)\n"
                    "_IGVA([a, b], lambda: [1, 2])\n"
    );

    check_string(
            "const a, b = 1, 2;",

            "a, b = List2Assignable(_CGFW(lambda: [1, 2], 2))"
    );
}
