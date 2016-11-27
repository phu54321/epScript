//
// Created by 박현우 on 2016. 11. 28..
//

#include "tokenAdapter.h"

int tokenTypeConv(TokenType type) {
    switch(type) {
        case TOKEN_BITOR: return BITOR;
        case TOKEN_BITXOR: return BITXOR;
        case TOKEN_BITAND: return BITAND;
        case TOKEN_BITLSHIFT: return LSHIFT;
        case TOKEN_BITRSHIFT: return RSHIFT;

        case TOKEN_PLUS: return PLUS;
        case TOKEN_MINUS: return MINUS;
        case TOKEN_DIVIDE: return DIVIDE;
        case TOKEN_MULTIPLY: return MULTIPLY;
        case TOKEN_MOD: return MOD;

        case TOKEN_NUMBER: return NUMBER;
        case TOKEN_NAME: return NAME;
        case TOKEN_ASSIGN: return ASSIGN;
        case TOKEN_COMMA: return COMMA;
        default: return -1;
    }
}