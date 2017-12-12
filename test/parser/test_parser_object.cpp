//
// Created by phu54321 on 2017-12-10.
//

#include "test_parser.hpp"

TEST_SUITE("Object tests");

TEST_CASE("Import parsing") {
    check("object/object_empty.eps", "object/object_empty.py");
}
