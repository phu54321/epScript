//
// Created by phu54321 on 2017-01-09.
//

#include "utils.h"
#include "parser/parser.h"
#include <stdexcept>
#include <string.h>
#include <vector>

extern bool NO_EPSPY;
extern bool MAP_DEBUG;

extern "C" {
void EPS_EXPORT setDebugMode(int set) {
    MAP_DEBUG = set != 0;
}

const char *EPS_EXPORT compileString(
        const char *modname,
        const char *rawcode
) {
    NO_EPSPY = true;

    // Remove \r from code
    std::vector<char> cleanCode;
    cleanCode.reserve(strlen(rawcode) + 1);
    const char* p = rawcode;
    while(*p) {
        if(*p != '\r') cleanCode.push_back(*p);
        p++;
    }
    std::string code(cleanCode.begin(), cleanCode.end());

    try {
        auto parsed = ParseString(modname, code);
        parsed = addStubCode(parsed);
        char *s = new char[parsed.size() + 1];
        memcpy(s, parsed.data(), parsed.size());
        s[parsed.size()] = '\0';
        NO_EPSPY = false;
        return s;
    } catch (std::runtime_error e) {
        fprintf(stderr, "Error occured : %s\n", e.what());
        NO_EPSPY = false;
        return nullptr;
    }
}

void EPS_EXPORT freeCompiledResult(const char *str) {
    delete[] str;
}
}

