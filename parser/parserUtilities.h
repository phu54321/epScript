//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PARSERUTILITIES_H
#define EPSCRIPT_PARSERUTILITIES_H

#include <string>
#include <iostream>
#include <functional>

#include "tokenizer/tokenizer.h"
#include "generator/pygen.h"
#include "generator/closure.h"

extern int tmpIndex;
extern PyGenerator* pGen;
extern ClosureManager* closure;

void checkIsConstant(std::string& name);
void checkIsVariable(std::string& name);
void checkIsFunction(std::string& name);
void checkIsRValue(std::string& name);

Token* genEmpty();
Token* genTemp(Token* lineSrc);
Token* mkTokenTemp(Token* a);
Token* commaConcat(Token* a, Token* b);
Token* binaryMerge(Token* a, const std::string& opstr, Token* b);

void commaListIter(std::string& s, std::function<void(std::string&)> func);
void throw_error(int code, const std::string& message);
int resetParserErrorNum();
////

// trim from start
std::string trim(std::string s);
std::string iwCollapse(const std::string& in);
void funcNamePreprocess(std::string& s);
std::string addStubCode(const std::string& s);

#endif //EPSCRIPT_PARSERUTILITIES_H
