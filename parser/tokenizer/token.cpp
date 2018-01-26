//
// Created by phu54321 on 2018-01-26.
//

#include "token.h"

#ifdef MEMORY_DEBUG
int allocatedTokenNum = 0;
#define ADDTOKCOUNT allocatedTokenNum++
#define RMVTOKCOUNT allocatedTokenNum--
#else
#define ADDTOKCOUNT
#define RMVTOKCOUNT
#endif

Token::Token(const std::string& data, Token* lineSrc)
        : type(TOKEN_TEMP), data(data), line(lineSrc->line) { ADDTOKCOUNT; }
Token::Token(TokenType type, int line)
        : type(type), line(line) { ADDTOKCOUNT; }
Token::Token(TokenType type, const std::string& data, int line)
        : type(type), data(data), line(line) { ADDTOKCOUNT; }
Token::~Token() {
    for(Token* st : subToken) delete st;
    RMVTOKCOUNT;
}

