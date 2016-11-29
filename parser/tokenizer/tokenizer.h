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
    TOKEN_TEMP,

    // Keywords
    TOKEN_FROM,
    TOKEN_IMPORT,
    TOKEN_VAR,
    TOKEN_CONST,
    TOKEN_FUNCTION,
    TOKEN_L2V,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_RETURN,

    // Identifiers
    TOKEN_NAME,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_CONDITION,
    TOKEN_ACTION,

    TOKEN_UNITNAME,
    TOKEN_LOCNAME,
    TOKEN_MAPSTRING,
    TOKEN_SWITCHNAME,

    // Operators
    TOKEN_ASSIGN,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MOD,
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
    TOKEN_COLON,
    TOKEN_SEMICOLON,
};

struct Token {
    Token(const std::string& data, Token* lineSrc)
            : type(TOKEN_TEMP), data(data), line(lineSrc->line) {}
    Token(TokenType type, int line)
            : type(type), line(line) {}
    Token(TokenType type, const std::string& data, int line)
            : type(type), data(data), line(line) {}
    int type;
    std::string data;
    int line;
};


class TokenizerImpl;
class Tokenizer {
public:
    Tokenizer(const std::string& data);
    ~Tokenizer();

    Token* getToken();
    int getCurrentLine() const;
    std::string getCurrentLineString() const;

private:
    TokenizerImpl* _impl;
};

#endif //EPSCRIPT_TOKENIZER_H
