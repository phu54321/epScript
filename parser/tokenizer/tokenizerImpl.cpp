//
// Created by 박현우 on 2016. 11. 27..
//

#include "tokenizerImpl.h"
#include "tokChars.h"
#include "condAct.h"
#include <string.h>
#include <assert.h>

TokenizerImpl::TokenizerImpl(const std::string& is)
        : data(is.begin(), is.end()) {
    // Negative -> Positive
    data.push_back(EOF);
    data.push_back(0);
    cursor = data.data();
    line = 1;
}

TokenizerImpl::~TokenizerImpl() {}

////

int TokenizerImpl::getCurrentLine() const {
    return line;
}

std::string TokenizerImpl::getCurrentLineString() const {
    const char *lineStart = cursor - 1, *lineEnd = cursor;
    while(lineStart > data.data() && *lineStart != '\n') lineStart--;
    if(*lineStart == '\n') lineStart++;
    while(*lineEnd != EOF && *lineEnd != '\n') lineEnd++;
    return std::string(lineStart, lineEnd - lineStart);
}

Token* TokenizerImpl::TK(TokenType type) {
    return new Token(type, line);
}

Token* TokenizerImpl::TK(TokenType type, const std::string& str) {
    return new Token(type, str, line);
}

#define MATCHSTR(s, tokenType) \
    if(strncmp(s, cursor, sizeof(s) - 1) == 0) { \
        cursor += sizeof(s) - 1; \
        return TK(tokenType, s); \
}

static_assert(sizeof("string") == 7, "sizeof string should be strlen(str) + 1");

Token* TokenizerImpl::getToken() {
    do {
        // Skip spaces, including newline
        while (isSpaceOrNewline(*cursor)) {
            // Skipped through newline.
            if (*cursor == '\n') {
                line++;
                cursor++;
            } else cursor++;
        }

        // Skip line comments
        if (cursor[0] == '/' && cursor[1] == '/') {
            while(*cursor != '\n') cursor++;
            continue;
        }
        break;
    } while(true);

    // EOF check
    assert(cursor <= data.data() + data.size() - 2);
    if(cursor >= data.data() + data.size() - 2) {
        return nullptr;  // EOF
    }

    // Identifiers
    if(isNameLeadChar(*cursor)) {
        const char* idfStart = cursor;
        while(isNameBodyChar(*(++cursor)));
        std::string identifier(idfStart, cursor - idfStart);

        if(identifier == "from") return TK(TOKEN_FROM);
        if(identifier == "import") return TK(TOKEN_IMPORT);
        if(identifier == "var") return TK(TOKEN_VAR);
        if(identifier == "const") return TK(TOKEN_CONST);
        if(identifier == "function") return TK(TOKEN_FUNCTION);
        if(identifier == "if") return TK(TOKEN_IF);
        if(identifier == "elif") return TK(TOKEN_ELIF);
        if(identifier == "else") return TK(TOKEN_ELSE);
        if(identifier == "for") return TK(TOKEN_FOR);
        if(identifier == "while") return TK(TOKEN_WHILE);
        if(identifier == "break") return TK(TOKEN_BREAK);
        if(identifier == "continue") return TK(TOKEN_CONTINUE);
        if(identifier == "return") return TK(TOKEN_RETURN);

        if(isConditionName(identifier)) return TK(TOKEN_CONDITION, identifier);
        if(isActionName(identifier)) return TK(TOKEN_ACTION, identifier);

        return TK(TOKEN_NAME, identifier);
    }

    // String
    if(*cursor == '\"') {
        std::vector<char> buffer;  // String to hold escaped content.
        buffer.push_back('\"');
        cursor++;

        while(*cursor != '\"') {
            if(*cursor == '\n' || *cursor == EOF) { // Line end during string - Invalid token
                // We don't skip newlines We need to count lines using them.
                // Return invalid token message
                return TK(TOKEN_INVALID);
            }
            else if(*cursor == '\\') {  // Escape character
                cursor++;
                if(*cursor == '\n') {
                    cursor++;
                }

                // No special procesing is required. Python will take care of that.
                else {
                    buffer.push_back('\\');
                    buffer.push_back(*cursor);
                    cursor++;
                }
            }
            else {
                buffer.push_back(*cursor);
                cursor++;
            }
        }
        cursor++;
        buffer.push_back('\"');
        return TK(TOKEN_STRING, std::string(buffer.data(), buffer.size()));
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

    // Mapdata getter
    MATCHSTR("$U", TOKEN_UNITNAME);
    MATCHSTR("$L", TOKEN_LOCNAME);
    MATCHSTR("$S", TOKEN_SWITCHNAME);
    MATCHSTR("$T", TOKEN_MAPSTRING);

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
    MATCHSTR(";", TOKEN_SEMICOLON);

    printf("Unknown token %c(%d)\n", *cursor, *cursor);
    cursor++;  // Skip invalid token
    return TK(TOKEN_INVALID);
}
