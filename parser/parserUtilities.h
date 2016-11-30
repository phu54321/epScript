//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PARSERUTILITIES_H
#define EPSCRIPT_PARSERUTILITIES_H

#include <string>
#include <iostream>
#include <functional>

#include "tokenizer/tokenizer.h"

extern bool errorOccured;
extern int tmpIndex;
Token* genTemp(Token* lineSrc);

void commaListIter(std::string& s, std::function<void(std::string&)> func);
void throw_error(int line, int code, const std::string& message);

////

// trim from start
std::string trim(std::string s);
Token* mkTokenTemp(Token* a, PyGenerator& pGen);
Token* binaryMerge(Token* a, const std::string& opstr, Token* b, PyGenerator& pGen);

std::string iwCollapse(const std::string& in);
void funcNamePreprocess(std::string& s);
std::string addStubCode(const std::string& s);

#endif //EPSCRIPT_PARSERUTILITIES_H
