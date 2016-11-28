//
// Created by 박현우 on 2016. 11. 26..
//

#include "tokenizer.h"
#include "tokenizerImpl.h"

Tokenizer::Tokenizer(std::istream& is) : _impl(new TokenizerImpl(is)) {}
Tokenizer::~Tokenizer() { delete _impl; }
Token* Tokenizer::getToken() { return _impl->getToken(); }
int Tokenizer::getCurrentLine() const { return _impl->getCurrentLine(); }
std::string Tokenizer::getCurrentLineString() const { return _impl->getCurrentLineString(); }
