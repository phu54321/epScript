#include <string>
#include <stdexcept>

std::string getFile(const std::string& fname) {
    FILE* fp = fopen(fname.c_str(), "rb");
    if(fp == nullptr) {
        throw std::runtime_error("Input file not found : " + fname);
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char* data = new char[fsize];
    fread(data, 1, fsize, fp);
    fclose(fp);
    std::string code(data, fsize);
    delete[] data;
    return code;
}
