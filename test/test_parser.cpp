#include "../parser/tokenAdapter.h"
#include "doctest.hpp"
#include <string>
#include <cstdio>
#include <regex>

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    FILE* fp = fopen(dataname.c_str(), "r");
    if(fp == nullptr) {
        return "";
    }
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    rewind(fp);

    char* data = new char[fsize];
    fread(data, 1, fsize, fp);
    fclose(fp);
    std::string code(data, fsize);
    delete[] data;
    return code;
}

std::regex commentLine("^ *#.+\n");
std::regex commentLineML("\n *#.+");
std::string uncommentString(std::string&& data) {
    std::string s = std::regex_replace(data, commentLine, "");
    return std::regex_replace(s, commentLineML, "");
}


#define check(infile, outfile) CHECK(uncommentString(ParseString(get_testdata(infile))) == get_testdata(outfile))

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
                REQUIRE(ParseString("var a;") == "# (Line 1) var a;\na = EUDVariable()\n");
                REQUIRE_THROWS_AS(ParseString("b = 2;"), std::runtime_error);
    }
}

TEST_CASE("Control block parsing") {
    check("ctrlstru/ctrlstru_if.eps", "ctrlstru/ctrlstru_if.py");
    check("ctrlstru/ctrlstru_while.eps", "ctrlstru/ctrlstru_while.py");
}

TEST_SUITE_END();
