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

void checkIsConstant(std::string& name, int line);
void checkIsVariable(std::string& name, int line);
void checkIsFunction(std::string& name, int line);
void checkIsRValue(std::string& name, int line);

Token* genEmpty();
Token* genTemp(Token* lineSrc);
Token* mkTokenTemp(Token* a);
Token* commaConcat(Token* a, Token* b);
Token* binopConcat(Token* a, const std::string& opstr, Token* b);

void commaListIter(std::string& s, std::function<void(std::string&)> func);
void throw_error(int code, const std::string& message, int line = -1);
int resetParserErrorNum();
////

// trim from start
std::string trim(std::string s);
std::string iwCollapse(const std::string& in);
void funcNamePreprocess(std::string& s);
std::string impPathProcess(const std::string& s);
std::string impPathGetModule(const std::string& s);

std::string addStubCode(const std::string& s);

#endif //EPSCRIPT_PARSERUTILITIES_H
