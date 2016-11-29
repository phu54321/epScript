#include "../parser/parser.h"
#include "doctest.hpp"
#include <string>
#include <cstdio>
#include <regex>

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    return getFile(dataname);
}

std::regex commentLine("^ *#.+\n");
std::regex commentLineML("\n *#.+");
std::string uncommentString(std::string&& data) {
    std::string s = std::regex_replace(data, commentLine, "");
    return std::regex_replace(s, commentLineML, "");
}

std::regex crlf("\r\n");
std::string unCRLF(const std::string& in) {
    return std::regex_replace(in, crlf, "\n");
}

#define check(infile, outfile) CHECK(uncommentString(ParseString(get_testdata(infile))) == unCRLF(get_testdata(outfile)))

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
                REQUIRE(uncommentString(ParseString("var a;")) == "a = EUDCreateVariables(1)\n");
                REQUIRE_THROWS_AS(ParseString("b = 2;"), std::runtime_error);
    }
}

TEST_CASE("Control block parsing") {
    check("ctrlstru/ctrlstru_if.eps", "ctrlstru/ctrlstru_if.py");
    check("ctrlstru/ctrlstru_while.eps", "ctrlstru/ctrlstru_while.py");
}

TEST_SUITE_END();
