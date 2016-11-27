//
// Created by 박현우 on 2016. 11. 26..
//

#include "tokenizer.h"

class TokenizerImpl {
public:
    TokenizerImpl(std::istream& is);
    ~TokenizerImpl();
    TokenPtr getToken();

private:
    TokenPtr TK(TokenType type) {
        return std::make_shared<Token>(type, line);
    }

    TokenPtr TK(TokenType type, const std::string& data) {
        return std::make_shared<Token>(type, data, line);
    }

    std::vector<char> data;
    char* cursor;
    int line;
};

Tokenizer::Tokenizer(std::istream& is) : _impl(new TokenizerImpl(is)) {}
Tokenizer::~Tokenizer() { delete _impl; }
TokenPtr Tokenizer::getToken() { return _impl->getToken(); }

////

TokenizerImpl::TokenizerImpl(std::istream& is)
        : data(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()) {
    // Negative -> Positive
    data.push_back(EOF);
    data.push_back(0);
    cursor = data.data();
    line = 1;
}

TokenizerImpl::~TokenizerImpl() {}

////

#define MATCHSTR(s, tokenType) \
    if(strncmp(s, cursor, sizeof(s) - 1) == 0) { \
        cursor += sizeof(s) - 1; \
        return TK(tokenType); \
}

static_assert(sizeof("string") == 7, "sizeof string should be strlen(str) + 1");


constexpr bool isNameLeadChar(char ch) {
    return (
            ch == '_' ||
            ('a' <= ch && ch <= 'z') ||
            ('A' <= ch && ch <= 'Z')
    );
}

constexpr bool isNameBodyChar(char ch) {
    return (
            ch == '_' ||
            ('a' <= ch && ch <= 'z') ||
            ('A' <= ch && ch <= 'Z') ||
            ('0' <= ch && ch <= '9')
    );
}

constexpr bool isSpaceChar(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

TokenPtr TokenizerImpl::getToken() {
    // Skip spaces
    while(isSpaceChar(*cursor)) {
        if(*cursor == '\n') line++;
        cursor++;
    }

    // EOF check
    if(cursor == data.data() + data.size() - 2) {
        return nullptr;  // EOF
    }

    // Identifiers
    if(isNameLeadChar(*cursor)) {
        const char* idfStart = cursor;
        while(isNameBodyChar(*(++cursor)));
        std::string identifier(idfStart, cursor - idfStart);

        if(identifier == "var") return TK(TOKEN_VAR);
        if(identifier == "function") return TK(TOKEN_FUNCTION);
        if(identifier == "if") return TK(TOKEN_IF);
        if(identifier == "elif") return TK(TOKEN_ELIF);
        if(identifier == "else") return TK(TOKEN_ELSE);
        if(identifier == "for") return TK(TOKEN_FOR);
        if(identifier == "while") return TK(TOKEN_WHILE);
        if(identifier == "break") return TK(TOKEN_BREAK);
        if(identifier == "continue") return TK(TOKEN_CONTINUE);
        return TK(TOKEN_NAME, identifier);
    }

    // Operators
    MATCHSTR("+", TOKEN_PLUS);
    MATCHSTR("-", TOKEN_MINUS);
    MATCHSTR("*", TOKEN_MULTIPLY);
    MATCHSTR("/", TOKEN_DIVIDE);

    MATCHSTR("==", TOKEN_EQ);
    MATCHSTR("<=", TOKEN_LE);
    MATCHSTR(">=", TOKEN_GE);
    MATCHSTR("<", TOKEN_LT);
    MATCHSTR(">", TOKEN_GT);
    MATCHSTR("!=", TOKEN_NE);

    MATCHSTR("=", TOKEN_ASSIGN);

    return TK(TOKEN_INVALID);
}
