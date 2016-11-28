//
// Created by 박현우 on 2016. 11. 28..
//

#include "tokenAdapter.h"

int getConvertedType(int type) {
    switch(type) {
        case TOKEN_COMMA: return COMMA;
        case TOKEN_ASSIGN: return ASSIGN;
        case TOKEN_LOR: return LOR;
        case TOKEN_LAND: return LAND;
        case TOKEN_LNOT: return LNOT;
        case TOKEN_EQ: return EQ;
        case TOKEN_LE: return LE;
        case TOKEN_LT: return LT;
        case TOKEN_GE: return GE;
        case TOKEN_GT: return GT;
        case TOKEN_NE: return NE;
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
        case TOKEN_ELSE: return ELSE;
        case TOKEN_NAME: return NAME;
        case TOKEN_NUMBER: return NUMBER;
        case TOKEN_BITNOT: return BITNOT;
        case TOKEN_SEMICOLON: return SEMICOLON;
        case TOKEN_LBRACKET: return LBRACKET;
        case TOKEN_RBRACKET: return RBRACKET;
        case TOKEN_LSQBRACKET: return LSQBRACKET;
        case TOKEN_RSQBRACKET: return RSQBRACKET;
        case TOKEN_IF: return IF;
        case TOKEN_LPAREN: return LPAREN;
        case TOKEN_RPAREN: return RPAREN;
        case TOKEN_WHILE: return WHILE;
        case TOKEN_CONTINUE: return CONTINUE;
        case TOKEN_BREAK: return BREAK;
        case TOKEN_VAR: return VAR;
        case TOKEN_FUNCTION: return FUNCTION;
        case TOKEN_RETURN: return RETURN;
        default: return -1;
    }
}

bool tokenTypeConv(Token* token) {
    int newtype = getConvertedType(token->type);
    if(newtype == -1) return false;
    else {
        token->type = newtype;
        return true;
    }
}