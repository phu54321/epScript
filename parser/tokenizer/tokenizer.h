//
// Created by 박현우 on 2016. 11. 26..
//

#ifndef EPSCRIPT_TOKENIZER_H
#define EPSCRIPT_TOKENIZER_H

#include <istream>
#include <vector>
#include <memory>

enum TokenType {
    TOKEN_INVALID,

    // Variables
    TOKEN_VAR,
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_PASS,

    // Identifiers
    TOKEN_NAME,
    TOKEN_NUMBER,

    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MOD,
    TOKEN_ASSIGN,
    TOKEN_BITLSHIFT,
    TOKEN_BITRSHIFT,
    TOKEN_BITAND,
    TOKEN_BITOR,
    TOKEN_BITXOR,
    TOKEN_BITNOT,
    TOKEN_LAND,
    TOKEN_LOR,
    TOKEN_LNOT,
    TOKEN_EQ,
    TOKEN_LE,
    TOKEN_GE,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_NE,

    // Other tokens
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LSQBRACKET,
    TOKEN_RSQBRACKET,
    TOKEN_COMMA,
    TOKEN_COLON
};

struct Token {
    Token(TokenType type, int line)
            : type(type), line(line) {}
    Token(TokenType type, const std::string& data, int line)
            : type(type), data(data), line(line) {}
    TokenType type;
    std::string data;
    int line;
};

using TokenPtr = std::shared_ptr<Token>;

class TokenizerImpl;
class Tokenizer {
public:
    Tokenizer(std::istream& is);
    ~Tokenizer();

    TokenPtr getToken();

private:
    TokenizerImpl* _impl;
};

#endif //EPSCRIPT_TOKENIZER_H
