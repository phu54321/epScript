#include "../parser/parser.h"
#include "../utils.h"
#include "doctest.hpp"
#include <stdexcept>
#include <string.h>
#include <vector>

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    return getFile(dataname);
}


std::string unindentString(const std::string& data) {
    std::vector<char> sbuf;
    bool isNewline = true;
    size_t index = 0, dlen = data.size();
    sbuf.reserve(dlen);

    while(index < dlen) {
        if(isNewline && data[index] == ' ') {
            index += 4;  // unindent
            if(index >= dlen) break;
        }
        isNewline = false;

        sbuf.push_back(data[index]);
        if(data[index] == '\n') isNewline = true;
        index++;
    }
    return std::string(sbuf.begin(), sbuf.end());
}

void checkBlock(const std::string &input, const std::string &desiredOutput) {
    std::string output = ParseString("test", "function testf() {" + input + "}", false);

    // Remove header
    const char *header = "@EUDFunc\n"
            "def f_testf():\n";
            REQUIRE(strncmp(output.c_str(), header, strlen(header)) == 0);
    output = unindentString(output.substr(strlen(header)));
            CHECK(output == desiredOutput);
}

extern bool NO_EPSPY;

#define check(infile, outfile) CHECK_EQ(ParseString("test", get_testdata(infile), false), get_testdata(outfile))

TEST_SUITE("Parser tests");

TEST_CASE("test tool test") {
    CHECK(unindentString("    asdf\n    zxcv\n") == "asdf\nzxcv\n");
    checkBlock("", "pass\n");
}

TEST_CASE("Simple expression parsing") {
    SUBCASE("Simple arithmetic") {
        checkBlock("return 1 + 2;", "EUDReturn(1 + 2)\n");
        checkBlock("return 1 * 2;", "EUDReturn(1 * 2)\n");
        checkBlock("return 1 + 2 * 3;", "EUDReturn(1 + 2 * 3)\n");
        checkBlock("return dwread_epd(0);", "EUDReturn(f_dwread_epd(0))\n");
    }

    SUBCASE("Error handling") {
        // Plain expression cannot appear in program-level
                CHECK((ParseString("test", "2;"), getParseErrorNum() > 0));
    }


    SUBCASE("Global variable management") {
        // Variable declaration is allowed
                CHECK(ParseString("test", "var a;", false) == "a = EUDVariable()\n");
        // Cannot assign varable on global scope
                CHECK((ParseString("test", "var b; b = 2;"), getParseErrorNum() > 0));
    }
}

TEST_CASE("Control block parsing") {
    // Logical operator precedence
    checkBlock(
            "if(1 == 2 || 2 + 3 == 5 && 7 == 8) return 3;",

            "if EUDIf()(EUDOr(1 == 2, [2 + 3 == 5, 7 == 8])):\n"
            "    EUDReturn(3)\n"
            "EUDEndIf()\n"
    );

    // If, ElseIf, Else
    checkBlock(
            "if(1 == 2) return 3;\n"
            "else if(4 == 5) return 6;\n"
            "else {\n"
            "    return 7;\n"
            "}",

            "if EUDIf()(1 == 2):\n"
            "    EUDReturn(3)\n"
            "if EUDElseIf()(4 == 5):\n"
            "    EUDReturn(6)\n"
            "if EUDElse()():\n"
            "    EUDReturn(7)\n"
            "EUDEndIf()\n"
    );

    // While
    checkBlock(
            "while(1 == 2) continue;",

            "if EUDWhile()(1 == 2):\n"
            "    EUDContinue()\n"
            "EUDEndWhile()\n"
    );

    check("ctrlstru/ctrlstru_foreach.eps", "ctrlstru/ctrlstru_foreach.py");
}

TEST_CASE("Import parsing") {
            CHECK(ParseString("test", "import a1;", false) == "from _epspy import a1\n");
            CHECK(ParseString("test", "import test.a1;", false) == "from test._epspy import a1\n");
            CHECK(ParseString("test", "import py_a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.py_a1;", false) == "from test import a1\n");
}

TEST_CASE("Other parsing") {
    check("auxtest.eps", "auxtest.py");
    check("method.eps", "method.py");
}


TEST_CASE("Import parsing with NO_EPSPY") {
    NO_EPSPY = true;
            CHECK(ParseString("test", "import a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.a1;", false) == "from test import a1\n");
            CHECK(ParseString("test", "import py_a1;", false) == "import a1\n");
            CHECK(ParseString("test", "import test.py_a1;", false) == "from test import a1\n");
    NO_EPSPY = false;
}

TEST_SUITE_END();
