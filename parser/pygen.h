//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PYGEN_H
#define EPSCRIPT_PYGEN_H

#include <string>
#include <ostream>

class PyGeneratorBuf;
class PyGenerator : public std::ostream {
public:
    PyGenerator();
    virtual ~PyGenerator();
    std::string str();
    void indent();
    void unindent();

private:
    PyGeneratorBuf* pbuf;
};

#endif //EPSCRIPT_PYGEN_H
