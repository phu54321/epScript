//
// Created by phu54321 on 2018-01-26.
//

#include "traceUtils.h"

extern int currentTokenizingLine;
void writeTraceInfo(std::ostream& os, Token* tok) {
    int line = tok ? tok->line : currentTokenizingLine;
    os << "EUDTraceLog(" << line << ")\n";
}
