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

TokenPtr TokenizerImpl::TK(TokenType type, int data) {
    return std::make_shared<Token>(type, data, line);
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

        if(identifier == "var") return TK(VAR);
        if(identifier == "function") return TK(FUNCTION);
        if(identifier == "if") return TK(IF);
        if(identifier == "elif") return TK(ELIF);
        if(identifier == "else") return TK(ELSE);
        if(identifier == "for") return TK(FOR);
        if(identifier == "while") return TK(WHILE);
        if(identifier == "break") return TK(BREAK);
        if(identifier == "continue") return TK(CONTINUE);
        if(identifier == "pass") return TK(PASS);
        return TK(NAME, identifier);
    }

    // Numbers
    if('0' <= *cursor && *cursor <= '9') {
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
            return TK(NUMBER, num);
        }
        // Decimal number
        else {
            int num = 0;
            while('0' <= *cursor && *cursor <= '9') {
                num = num * 10 + (*cursor - '0');
                cursor++;
            }
            return TK(NUMBER, num);
        }
    }

    // Brackets
    MATCHSTR("(", TOKEN_LPAREN);
    MATCHSTR(")", TOKEN_RPAREN);
    MATCHSTR("[", TOKEN_LSQBRACKET);
    MATCHSTR("]", TOKEN_RSQBRACKET);

    // Operators
    MATCHSTR("&&", LAND);
    MATCHSTR("||", LOR);

    MATCHSTR("<<", LSHIFT);
    MATCHSTR(">>", RSHIFT);
    MATCHSTR("~", BITNOT);
    MATCHSTR("&", BITAND);  // After LAND
    MATCHSTR("|", BITOR);  // After LOR
    MATCHSTR("^", BITXOR);

    MATCHSTR("==", EQ);
    MATCHSTR("<=", LE);
    MATCHSTR(">=", GE);
    MATCHSTR("<", LT);  // After LSHIFT
    MATCHSTR(">", GT);  // After RSHIFT
    MATCHSTR("!=", NE);  // After LNOT

    MATCHSTR("!", LNOT);

    MATCHSTR("+", PLUS);
    MATCHSTR("-", MINUS);
    MATCHSTR("*", MULTIPLY);
    MATCHSTR("/", DIVIDE);

    MATCHSTR("=", ASSIGN);  // After Comparators

    return TK(INVALID);
}
