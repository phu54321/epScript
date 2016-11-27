//
// Created by 박현우 on 2016. 11. 27..
//

#ifndef EPSCRIPT_TOKENIZERIMPL_H
#define EPSCRIPT_TOKENIZERIMPL_H

#include "tokenizer.h"
#include "tokIndent.h"

class TokenizerImpl {
public:
    TokenizerImpl(std::istream& is);
    ~TokenizerImpl();
    TokenPtr getToken();

private:
    TokenPtr TK(TokenType type);
    TokenPtr TK(TokenType type, const std::string& rawstr, int data);
    TokenPtr TK(TokenType type, const std::string& data);

private:
    TokIndent indenter;
    std::vector<char> data;
    char* cursor;
    int line;

};

#endif //EPSCRIPT_TOKENIZERIMPL_H
