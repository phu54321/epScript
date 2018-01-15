//
// Created by phu54321 on 2018-01-16.
//

#include "../test_base.hpp"


TEST_CASE("Simple arithmetic") {
    checkBlock("return 1 + 2;", "EUDReturn(1 + 2)\n");
    checkBlock("return 1 * 2;", "EUDReturn(1 * 2)\n");
    checkBlock("return 1 + 2 * 3;", "EUDReturn(1 + 2 * 3)\n");
    checkBlock("return dwread_epd(0);", "EUDReturn(f_dwread_epd(0))\n");
}
