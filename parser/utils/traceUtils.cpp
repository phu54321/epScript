//
// Created by phu54321 on 2018-01-26.
//

#include "traceUtils.h"

extern int currentTokenizingLine;
extern bool MAP_DEBUG;

void writeTraceInfo(std::ostream& os, Token* tok) {
    if (MAP_DEBUG) {
        int line = tok ? tok->line : currentTokenizingLine;
        os << "EUDTraceLog(" << line << ")\n";
    }
}
