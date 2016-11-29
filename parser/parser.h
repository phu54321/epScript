#ifndef EPSCRIPT_PRASER_H
#define EPSCRIPT_PRASER_H

#include <string>
std::string getFile(const std::string& fname);
std::string ParseString(const std::string& code);
std::string addStubCode(const std::string& _s);

#endif //EPSCRIPT_PRASER_H
