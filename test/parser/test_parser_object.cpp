//
// Created by phu54321 on 2017-12-10.
//

#include "test_parser.hpp"

TEST_CASE("Simple object parsing") {
    SECTION("Empty object definition & initialization") {
        check_string(
                "object X {} const t = X();",
                "class X(EUDStruct):\n    _fields_ = []\n\nt = _CGFW(lambda: [X()], 1)[0]\n"
        );
    }

    SECTION("Member variable") {
        check_string(
                "object X { var x, y; }",
                "class X(EUDStruct):\n    _fields_ = ['x', 'y', ]\n"
        );
    }
}
