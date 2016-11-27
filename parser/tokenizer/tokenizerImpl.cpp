//
// Created by 박현우 on 2016. 11. 27..
//

#include "tokenizerImpl.h"
#include "tokChars.h"

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

TokenPtr TokenizerImpl::TK(TokenType type) {
    return std::make_shared<Token>(type, line);
}

TokenPtr TokenizerImpl::TK(TokenType type, const std::string& str) {
    return std::make_shared<Token>(type, str, line);
}

#define MATCHSTR(s, tokenType) \
    if(strncmp(s, cursor, sizeof(s) - 1) == 0) { \
        cursor += sizeof(s) - 1; \
        return TK(tokenType, s); \
}

static_assert(sizeof("string") == 7, "sizeof string should be strlen(str) + 1");

TokenPtr TokenizerImpl::getToken() {
    // Skip spaces, including newline
    while(isSpaceOrNewline(*cursor)) {
        // Skipped through newline.
        if(*cursor == '\n') {
            line++;
            cursor++;
        }
        else cursor++;
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
        if(identifier == "pass") return TK(TOKEN_PASS);
        return TK(TOKEN_NAME, identifier);
    }

    // Numbers
    if('0' <= *cursor && *cursor <= '9') {
        const char* numberStart = cursor;
        // Hexadecimal number
        if((
                (cursor[1] == 'x' || cursor[1] == 'X') &&
                isxdigit(cursor[2]))) {
            cursor += 2;
            int num = 0, chnum = 0;
            while((chnum = getXDigitInt(*cursor)) != -1) {
                num = (num << 4) | chnum;
                cursor++;
            }
            return TK(TOKEN_NUMBER, std::string(numberStart, cursor - numberStart));
        }
        // Decimal number
        else {
            int num = 0;
            while('0' <= *cursor && *cursor <= '9') {
                num = num * 10 + (*cursor - '0');
                cursor++;
            }
            return TK(TOKEN_NUMBER, std::string(numberStart, cursor - numberStart));
        }
    }

    // Operators
    MATCHSTR("&&", TOKEN_LAND);
    MATCHSTR("||", TOKEN_LOR);

    MATCHSTR("<<", TOKEN_BITLSHIFT);
    MATCHSTR(">>", TOKEN_BITRSHIFT);
    MATCHSTR("~", TOKEN_BITNOT);
    MATCHSTR("&", TOKEN_BITAND);  // After TOKEN_LAND
    MATCHSTR("|", TOKEN_BITOR);  // After TOKEN_LOR
    MATCHSTR("^", TOKEN_BITXOR);

    MATCHSTR("==", TOKEN_EQ);
    MATCHSTR("<=", TOKEN_LE);
    MATCHSTR(">=", TOKEN_GE);
    MATCHSTR("<", TOKEN_LT);  // After TOKEN_BITLSHIFT
    MATCHSTR(">", TOKEN_GT);  // After TOKEN_BITRSHIFT
    MATCHSTR("!=", TOKEN_NE);  // After TOKEN_LNOT

    MATCHSTR("!", TOKEN_LNOT);

    MATCHSTR("+", TOKEN_PLUS);
    MATCHSTR("-", TOKEN_MINUS);
    MATCHSTR("*", TOKEN_MULTIPLY);
    MATCHSTR("/", TOKEN_DIVIDE);
    MATCHSTR("%", TOKEN_MOD);

    MATCHSTR("=", TOKEN_ASSIGN);  // After Comparators

    // Special chars
    MATCHSTR("(", TOKEN_LPAREN);
    MATCHSTR(")", TOKEN_RPAREN);
    MATCHSTR("[", TOKEN_LSQBRACKET);
    MATCHSTR("]", TOKEN_RSQBRACKET);
    MATCHSTR("{", TOKEN_LBRACKET);
    MATCHSTR("}", TOKEN_RBRACKET);
    MATCHSTR(",", TOKEN_COMMA);
    MATCHSTR(":", TOKEN_COLON);

    return TK(TOKEN_INVALID);
}
