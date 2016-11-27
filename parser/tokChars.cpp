#include "tokChars.h"

bool isNameLeadChar(char ch) {
    return (
            ch == '_' ||
            ('a' <= ch && ch <= 'z') ||
            ('A' <= ch && ch <= 'Z')
    );
}

bool isNameBodyChar(char ch) {
    return (
            ch == '_' ||
            ('a' <= ch && ch <= 'z') ||
            ('A' <= ch && ch <= 'Z') ||
            ('0' <= ch && ch <= '9')
    );
}

bool isSpaceOrNewline(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

int getCharIndentLevel(char ch) {
    if(ch == ' ') return 1;
    else if(ch == '\t') return 4;
    else return 0;
}
