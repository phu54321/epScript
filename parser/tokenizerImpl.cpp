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
    reread:;

    // Unindentation may require several steps. Here we care that first.
    if(indenter.remainingIndentTokens() < 0) {
        indenter.unindent();
        return TK(TOKEN_UNINDENT);
    }

    // Skip spaces, including newline
    while(isSpaceOrNewline(*cursor)) {
        // Skipped through newline.
        if(*cursor == '\n') {
            line++;
            cursor++;

            // Get indent level after '\n'
            int chIndentLevel, totalIndentLevel = 0;
            while((chIndentLevel = getCharIndentLevel(*cursor)) != 0) {
                totalIndentLevel += chIndentLevel;
                cursor++;
            }

            // If line contains no content (blank or line comment only)
            // Skip that line and start reading again from that line.
            if (*cursor == '#' || *cursor == '\n' || *cursor == EOF) {
                // Skip until newline
                while(*cursor != EOF && *cursor != '\n') cursor++;
                goto reread;
            }

            // This line contains something, so we apply new indentation level here.
            if(!indenter.setCurrentLineIndent(totalIndentLevel)) {
                // Error occured. meaning we have to ignore this line completely.
                while(*cursor != EOF && *cursor != '\n') cursor++;
                return TK(TOKEN_INVALIDINDENT);
            }

            // Indent if nessecary
            if (indenter.remainingIndentTokens() > 0) {
                indenter.indent();
                return TK(TOKEN_INDENT);
            }
            else if(indenter.remainingIndentTokens() < 0) {
                indenter.unindent();
                return TK(TOKEN_UNINDENT);
            }
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

    // Brackets
    MATCHSTR("(", TOKEN_LPAREN);
    MATCHSTR(")", TOKEN_RPAREN);
    MATCHSTR("[", TOKEN_LSQBRACKET);
    MATCHSTR("]", TOKEN_RSQBRACKET);

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

    MATCHSTR("=", TOKEN_ASSIGN);  // After Comparators

    return TK(TOKEN_INVALID);
}
