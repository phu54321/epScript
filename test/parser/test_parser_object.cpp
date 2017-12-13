//
// Created by phu54321 on 2017-12-10.
//

#include "test_parser.hpp"

TEST_CASE("Simple object parsing") {
    check("object/object_empty.eps", "object/object_empty.py");
    check("object/object_members.eps", "object/object_members.py");
}
