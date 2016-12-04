#include <string>
#include <stdexcept>
#include <vector>
#include <regex>
#include <iostream>

#include "generator/pygen.h"
#include "generator/eudplibGlobals.h"
#include "parserUtilities.h"

extern int currentTokenizingLine;

int errorn = 0;

void throw_error(int code, const std::string& message, int line) {
    if (line == -1) line = currentTokenizingLine;
    if (errorn < 100) {
        std::cerr << "[Error " << code << "] Line " << line << " : " << message << std::endl;
        (*pGen) << "# [Error " << code << "] Line " << line << " : " << message << std::endl;
        if (++errorn == 100) {
            std::cerr << " - More than 100 errors occured. Stop printing errors" << std::endl;
        }
    }
}

int resetParserErrorNum() {
    errorn = 0;
    return 0;
}

int getParseErrorNum() {
    return errorn;
}


////

void commaListIter(std::string& s, std::function<void(std::string&)> func) {
    bool isFirst = true;
    std::string out;
    const char *p = s.c_str(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        std::string value(p, p2 - p);
        func(value);
        if(isFirst) isFirst = false;
        else out += ", ";
        out += value;
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }
    s = out;
}

void funcNamePreprocess(std::string& s) {
    if(isBuiltinFunc(s)) return;  // Some builtin function don't have f_ prefixes. (b2i4) Pass them as-is
    if(s[0] == '_' || ('A' <= s[0] && s[0] <= 'Z')) return;  // Name starts with uppercase -> Don't modify
    else s = "f_" + s;
}


////


std::string trim(std::string s) {
    // ltrim
    size_t startpos = s.find_first_not_of(" \t");
    if (std::string::npos != startpos)
    {
        s = s.substr(startpos);
    }

    // rtrim
    size_t endpos = s.find_last_not_of(" \t");
    if (std::string::npos != endpos)
    {
        s = s.substr(0, endpos + 1);
    }
    return s;
}


static std::regex iwCollapseRegex("\n( *)(_t\\d+) = (EUDWhile|EUDIf|EUDElseIf)\\(\\)\n\\1if \\2\\((.+)\\):");
std::string iwCollapse(const std::string& in) {
    return std::regex_replace(in, iwCollapseRegex, "\n$1if $3()($4):");
}

const char* stubCode =
        "## NOTE: THIS FILE IS GENERATED BY EPSCRIPT! DO NOT MODITY\n"
        "from eudplib import *\n"
        "\n"
        "def _SRET(v, klist):\n"
        "   return List2Assignable([v[k] for k in klist])\n"
        "\n"
        "def _SV(dL, sL):\n"
        "   [d << s for d, s in zip(FlattenList(dL), FlattenList(sL))]\n"
        "\n"
        "class _ATTW:\n"
        "   def __init__(self, obj, attrName):\n"
        "       self.obj = obj\n"
        "       self.attrName = attrName\n"
        "   def __lshift__(self, r):\n"
        "       setattr(self.obj, self.attrName, r)\n"
        "\n"
        "class _ARRW:\n"
        "    def __init__(self, obj, index):\n"
        "        self.obj = obj\n"
        "        self.index = index\n"
        "    def __lshift__(self, r):\n"
        "        self.obj[self.index] = r\n"
        "\n"
        "def _L2V(l):\n"
        "   ret = EUDVariable()\n"
        "   if EUDIf()(l):\n"
        "       ret << 1\n"
        "   if EUDElse()():\n"
        "       ret << 0\n"
        "   EUDEndIf()\n"
        "   return ret\n"
        "\n"
        "def _MVAR(vs):\n"
        "   return List2Assignable([\n"
        "       v if IsEUDVariable(v) else EUDVariable() << v\n"
        "       for v in FlattenList(vs)])\n"
        "\n"
        "## NOTE: THIS FILE IS GENERATED BY EPSCRIPT! DO NOT MODITY\n\n";

std::string addStubCode(const std::string& s) {
    return stubCode + s;
}
