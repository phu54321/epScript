// Streambuf

#include <string>
#include <streambuf>
#include <sstream>
#include "pygen.h"

class PyGeneratorBuf : public std::streambuf {
public:
    PyGeneratorBuf() : lineStart(false), justUnindented(false), currentIndent(0) {}
    ~PyGeneratorBuf() {}

    std::string str() { return os.str(); }
    void indent() {
        currentIndent += 4;
    }
    void unindent(bool issueNewline) {
        if(currentIndent == 0) {
            throw std::logic_error("Not enough closures");
        }
        currentIndent -= 4;
        if(issueNewline) justUnindented = true;
    }

    virtual int overflow (int c) {
        if(c == EOF) return EOF;

        char ch = static_cast<char>(c);

        // Indent at the start of the line
        if (lineStart) {
            if(justUnindented) {
                os.put('\n');
                justUnindented = false;
            }
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
    bool justUnindented;
};


PyGenerator::PyGenerator()
        : std::ostream(new PyGeneratorBuf) {
    pbuf = static_cast<PyGeneratorBuf *>(rdbuf());
}

PyGenerator::~PyGenerator() {
    delete pbuf;
}

std::string PyGenerator::str() {
    return pbuf->str();
}

void PyGenerator::indent() {
    pbuf->indent();
}

void PyGenerator::unindent(bool issueNewline) {
    pbuf->unindent(issueNewline);
}
