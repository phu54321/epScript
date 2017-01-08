//
// Created by phu54321 on 2017-01-09.
//

#include "utils.h"
#include "parser/parser.h"
#include <stdexcept>

extern "C" {
const char *EPS_EXPORT compileString(
        const char *modname,
        const char *code
) {
    try {
        auto parsed = ParseString(modname, code);
        parsed = addStubCode(parsed);
        char *s = new char[parsed.size() + 1];
        memcpy(s, parsed.data(), parsed.size());
        s[parsed.size()] = '\0';
        return s;
    } catch (std::runtime_error e) {
        fprintf(stderr, "Error occured : %s\n", e.what());
        return nullptr;
    }
}

void EPS_EXPORT freeCompiledResult(const char *str) {
    delete[] str;
}
}

