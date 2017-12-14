#include "../../parser/parser.h"
#include "../../utils.h"
#include "../catch.hpp"
#include <stdexcept>
#include <algorithm>
#include <string.h>
#include <vector>
#include "test_base.hpp"


std::string get_testdata(std::string dataname) {
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
