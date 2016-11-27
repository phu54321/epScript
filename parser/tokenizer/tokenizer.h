//
// Created by 박현우 on 2016. 11. 26..
//

#ifndef EPSCRIPT_TOKENIZER_H
#define EPSCRIPT_TOKENIZER_H

#include <istream>
#include <vector>
#include <memory>

enum TokenType {
    INVALID,

    // Variables
    VAR,
    FUNCTION,
    IF,
    ELIF,
    ELSE,
    FOR,
    WHILE,
    BREAK,
    CONTINUE,
    PASS,

    // Identifiers
    NAME,
    NUMBER,

    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    LSHIFT,
    RSHIFT,
    BITAND,
    BITOR,
    BITXOR,
    BITNOT,
    LAND,
    LOR,
    LNOT,
    EQ,
    LE,
    GE,
    LT,
    GT,
    NE,

    // Other tokens
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_INDENT,
    TOKEN_UNINDENT,
    TOKEN_INVALIDINDENT,
    TOKEN_LSQBRACKET,
    TOKEN_RSQBRACKET,
};

struct Token {
    Token(TokenType type, const std::string& data, int line)
            : type(type), dataString(data), dataNumber(0), line(line) {}
    Token(TokenType type, int line)
            : type(type), dataNumber(0), line(line) {}
    Token(TokenType type, int data, int line)
            : type(type), dataNumber(data), line(line) {}
    TokenType type;
    std::string dataString;
    int dataNumber;
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
