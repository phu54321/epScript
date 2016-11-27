#ifndef EPSCRIPT_TOKENADAPTER_H
#define EPSCRIPT_TOKENADAPTER_H

#include "tokenizer/tokenizer.h"
#include "epparser.h"

bool tokenTypeConv(Token* token);
std::string ParseString(const std::string& code);

#endif //EPSCRIPT_TOKENADAPTER_H
