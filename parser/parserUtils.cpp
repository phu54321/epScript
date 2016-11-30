#include <string>
#include <stdexcept>
#include <vector>

std::string getFile(const std::string& fname) {
    FILE* fp = fopen(fname.c_str(), "r");
    if(fp == nullptr) {
        throw std::runtime_error("Input file not found : " + fname);
    }

    fseek(fp, 0, SEEK_END);
    size_t fsize = static_cast<size_t>(ftell(fp));
    rewind(fp);

    std::vector<char> fdata;
    fdata.reserve(fsize);
    while(1) {
        char ch = fgetc(fp);
        if(feof(fp)) break;
        fdata.push_back(ch);
    }
    return std::string(fdata.begin(), fdata.end());
}
