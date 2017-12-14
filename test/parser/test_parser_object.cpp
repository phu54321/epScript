//
// Created by phu54321 on 2017-12-10.
//

#include "test_parser.hpp"

TEST_CASE("Simple object parsing") {
    check_file("object/object_empty.eps", "object/object_empty.py");
    check_file("object/object_members.eps", "object/object_members.py");
}
