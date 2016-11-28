// Streambuf

#include <string>
#include <streambuf>
#include <sstream>
#include <set>
#include <vector>
#include "pygen.h"

struct Closure {
    std::set<std::string> definedNames;
};

class PyGeneratorBuf : public std::streambuf {
public:
    PyGeneratorBuf() : lineStart(false), justUnindented(false) {
        _closureList.push_back(Closure());
    }
    ~PyGeneratorBuf() {}

    std::string str() { return os.str(); }
    void indent() {
        _closureList.push_back(Closure());
    }
    void unindent() {
        if(_closureList.size() == 1) {
            throw std::logic_error("Not enough closures");
        }
        _closureList.pop_back();
        justUnindented = true;
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
            for(int i = 0 ; i < (_closureList.size() - 1) * 4 ; i++) {
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

    bool namedef(const std::string& name) {
        auto& nameSet = _closureList[_closureList.size() - 1].definedNames;
        if(nameSet.find(name) != nameSet.end()) {
            return false;
        }
        nameSet.insert(name);
        return true;
    }

    bool undefined(const std::string& name) const {
        for(const auto& closure : _closureList) {
            const auto& nameSet = closure.definedNames;
            if(nameSet.find(name) != nameSet.end()) return false;
        }
        return true;
    }


private:
    std::ostringstream os;
    std::vector<Closure> _closureList;
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

void PyGenerator::unindent() {
    pbuf->unindent();
}

bool PyGenerator::namedef(const std::string &name) {
    return pbuf->namedef(name);
}

bool PyGenerator::undefined(const std::string &name) {
    return pbuf->undefined(name);
}