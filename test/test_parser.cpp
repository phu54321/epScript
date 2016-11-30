#include "../parser/parser.h"
#include "doctest.hpp"
#include <stdexcept>

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    return getFile(dataname);
}


#define check(infile, outfile) CHECK_EQ(ParseString(get_testdata(infile), false), get_testdata(outfile))

TEST_SUITE("Parser tests");

TEST_CASE("Simple expression parsing") {
    SUBCASE("Simple arithmetic") {
        check("arith/arith_add.eps", "arith/arith_add.py");
        check("arith/arith_times.eps", "arith/arith_times.py");
        check("arith/arith_prec.eps", "arith/arith_prec.py");
        check("arith/arith_fcall.eps", "arith/arith_fcall.py");
    }

    SUBCASE("Error handling") {
        // Plain expression cannot appear in program-level
                REQUIRE_THROWS_AS(ParseString("2;"), std::runtime_error);
    }


    SUBCASE("Variable assignment") {
                REQUIRE(ParseString("var a;", false) == "a = EUDCreateVariables(1)\n");
                REQUIRE_THROWS_AS(ParseString("b = 2;"), std::runtime_error);
    }
}

TEST_CASE("Control block parsing") {
    check("ctrlstru/ctrlstru_if.eps", "ctrlstru/ctrlstru_if.py");
    check("ctrlstru/ctrlstru_while.eps", "ctrlstru/ctrlstru_while.py");
    check("ctrlstru/ctrlstru_foreach.eps", "ctrlstru/ctrlstru_foreach.py");
}

TEST_SUITE_END();
