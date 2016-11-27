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

    // Identifiers
    TOKEN_NAME,
    TOKEN_NUMBER,

    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_LSHIFT,
    TOKEN_RSHIFT,
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
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LSQBRACKET,
    TOKEN_RSQBRACKET,
};

struct Token {
    Token(TokenType type, const std::string& data) : type(type), data(data) {}
    Token(TokenType type) : type(type) {}
    TokenType type;
    std::string data;
};

using TokenPtr = std::shared_ptr<Token>;


class Tokenizer {
public:
    Tokenizer(std::istream& is);
    ~Tokenizer();

    TokenPtr getToken();

private:
    std::vector<char> data;
    char* cursor;
};

#endif //EPSCRIPT_TOKENIZER_H
