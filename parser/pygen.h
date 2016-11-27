//
// Created by 박현우 on 2016. 11. 28..
//

#ifndef EPSCRIPT_PYGEN_H
#define EPSCRIPT_PYGEN_H

#include <string>
#include <sstream>
#include <ostream>
#include <streambuf>

class PyGeneratorBuf : public std::streambuf {
public:
    PyGeneratorBuf() : lineStart(false), currentIndent(0) {}
    ~PyGeneratorBuf() {}

    std::string str() { return os.str(); }
    void indent() { currentIndent += 4; }
    void unindent() {
        if(currentIndent == 0) throw std::logic_error("Negative currentIndent");
        currentIndent -= 4;
    }

    virtual int overflow (int c) {
        if(c == EOF) return EOF;

        char ch = static_cast<char>(c);

        // Indent at the start of the line
        if (lineStart) {
            // Sequential linebreaks -> don't indent empty line
            if(ch == '\n') {
                os.put(ch);
                return ch;
            }

            // Indent line
            for(int i = 0 ; i < currentIndent ; i++) {
                os.put(' ');
            }
            lineStart = false;
        }
        os.put(ch);

        // Set linestart at the end of the line
        if (ch == '\n') {
            lineStart = true;
        }
        return ch;
    }


private:
    std::ostringstream os;
    int currentIndent;
    bool lineStart;
};

class PyGenerator : public std::ostream {
public:
    PyGenerator() : std::ostream(new PyGeneratorBuf) { pbuf = static_cast<PyGeneratorBuf *>(rdbuf()); }
    virtual ~PyGenerator() { delete pbuf; }
    std::string str() { return pbuf->str(); }
    void indent() { pbuf->indent(); }
    void unindent() { pbuf->unindent(); }

private:
    PyGeneratorBuf* pbuf;
};

#endif //EPSCRIPT_PYGEN_H
