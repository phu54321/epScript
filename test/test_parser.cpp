#include "../parser/parser.h"
#include "../utils.h"
#include "doctest.hpp"
#include <stdexcept>

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    return getFile(dataname);
}


#define check(infile, outfile) CHECK_EQ(ParseString("test", get_testdata(infile), false), get_testdata(outfile))

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
                CHECK((ParseString("test", "2;"), getParseErrorNum() > 0));
    }


    SUBCASE("Variable assignment") {
                CHECK(ParseString("test", "var a;", false) == "a = EUDVariable()\n");
                CHECK((ParseString("test", "b = 2;"), getParseErrorNum() > 0));
    }
}

TEST_CASE("Control block parsing") {
    check("ctrlstru/ctrlstru_if.eps", "ctrlstru/ctrlstru_if.py");
    check("ctrlstru/ctrlstru_while.eps", "ctrlstru/ctrlstru_while.py");
    check("ctrlstru/ctrlstru_foreach.eps", "ctrlstru/ctrlstru_foreach.py");
}

TEST_CASE("Other parsing") {
    check("auxtest.eps", "auxtest.py");
    check("method.eps", "method.py");
}


TEST_SUITE_END();
