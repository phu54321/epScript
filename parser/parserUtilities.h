//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PARSERUTILITIES_H
#define EPSCRIPT_PARSERUTILITIES_H

#include "tokenizer/tokenizer.h"
#include "pygen.h"
#include <string>
#include <iostream>
#include <regex>
#include "eudplibGlobals.h"

static bool errorOccured = false;

static int tmpIndex = 0;
Token* genTemp(Token* lineSrc) {
    static char output[20] = "_t";
    sprintf(output, "_t%d", tmpIndex++);
    return new Token(output, lineSrc);
}

template <typename T>
void commaListIter(const std::string& s, T func) {
    const char *p = s.c_str(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        std::string value(p, p2 - p);
        func(value);
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }
}

static void throw_error(int line, int code, const std::string& message) {
    std::cerr << "[Error " << code << "] Line " << line << " : " << message << std::endl;
    errorOccured = true;
}

////

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

const int LENGTH_LIMIT = 60;

Token* mkTokenTemp(Token* a, PyGenerator& pGen) {
    if(a->data.size() > LENGTH_LIMIT) {
        Token* t = genTemp(a);
        pGen << t->data << " = " << a->data << std::endl;
        delete a;
        return t;
    }
    else {
        a->type = TOKEN_TEMP;
        return a;
    }
}

Token* binaryMerge(Token* a, const std::string& opstr, Token* b, PyGenerator& pGen) {
    b->data = a->data + (" " + opstr + " ") + b->data;
    delete a;
    return mkTokenTemp(b, pGen);
}


static std::regex iwCollapseRegex("\n( *)(_t\\d+) = (EUDWhile|EUDIf)\\(\\)\n\\1if \\2\\((.+)\\):");
std::string iwCollapse(const std::string& in) {
    return std::regex_replace(in, iwCollapseRegex, "\n$1if $3()($4):");
}

void funcNamePreprocess(std::string& s) {
    if(isBuiltinFunc(s)) return;  // Some builtin function don't have f_ prefixes. (b2i4) Pass them as-is
    if(s[0] == '_' || ('A' <= s[0] && s[0] <= 'Z')) return;  // Name starts with uppercase -> Don't modify
    else s = "f_" + s;
}

const char* stubCode =
        "# epScript support code\n"
        "\n"
        "from eudplib import *\n"
        "\n"
        "def _SRET(v, klist):\n"
        "    return (v[k] for k in klist)\n"
        "\n"
        "def _MVAR(vs):\n"
        "    rets = []\n"
        "    for v in FlattenList(vs):\n"
        "        if IsEUDVariable(v):\n"
        "            rets.append(v)\n"
        "        else:\n"
        "            var = EUDVariable()\n"
        "            var << v\n"
        "            rets.append(var)\n"
        "    return List2Assignable(rets)\n"
        "\n"
        "# epScript user code\n";

std::string postProcessCode(const std::string& _s) {
    std::string s = iwCollapse(_s);

    // Add default functions
    return stubCode + s;
}

#endif //EPSCRIPT_PARSERUTILITIES_H
