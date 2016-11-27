//
// Created by 박현우 on 2016. 11. 26..
//

#include "tokenizer.h"

Tokenizer::Tokenizer(std::istream& is)
        : data(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()) {
    // Negative -> Positive
    data.push_back(EOF);
    data.push_back(0);
    cursor = data.data();
}

Tokenizer::~Tokenizer() {}

////

static_assert(sizeof("string") == 7, "sizeof string should be strlen(str) + 1");

#define MATCHSTR(s, tokenType) \
    if(strncmp(s, cursor, sizeof(s) - 1) == 0) { \
        cursor += sizeof(s) - 1; \
        return std::make_shared<Token>(tokenType); \
}


TokenPtr Tokenizer::getToken() {
    if(cursor == data.data() + data.size() - 2) {
        return nullptr;  // EOF
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

    return std::make_shared<Token>(TOKEN_INVALID);
}
