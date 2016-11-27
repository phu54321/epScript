#ifndef EPSCRIPT_TOKENADAPTER_H
#define EPSCRIPT_TOKENADAPTER_H

#include "tokenizer/tokenizer.h"
#include "epparser.h"

int tokenTypeConv(TokenType type);
std::string ParseString(const std::string& code);

#endif //EPSCRIPT_TOKENADAPTER_H
