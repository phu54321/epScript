//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PARSERUTILITIES_H
#define EPSCRIPT_PARSERUTILITIES_H

#include "tokenizer/tokenizer.h"
#include <string>
#include <iostream>

static bool errorOccured = false;

static int tmpIndex = 0;
Token* genTemp(Token* lineSrc) {
    static char output[20] = "_t";
    sprintf(output, "_t%d", tmpIndex++);
    return new Token(output, lineSrc);
}

template <typename T>
void commaListIter(const std::string& s, T func) {
    const char *p = s.c_str(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        std::string value(p, p2 - p);
        func(value);
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }
}

static void throw_error(int line, int code, const std::string& message) {
    std::cout << "[Error " << code << "] Line " << line << " : " << message << std::endl;
    errorOccured = true;
}

////


// Loop block related
struct LBlock {
    std::string lbegin;
    std::string lcont;
    std::string lend;
};

std::vector<LBlock> lblocks;

LBlock* getLastBlock() {
    if(lblocks.empty()) return nullptr;
    return &lblocks[lblocks.size() - 1];
}

#endif //EPSCRIPT_PARSERUTILITIES_H
