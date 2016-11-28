#include <cstdio>
#include <fstream>
#include <iostream>
#include "parser/tokenAdapter.h"

static std::string getFile(const std::string& fname) {
    FILE* fp = fopen(fname.c_str(), "r");
    if(fp == nullptr) {
        return "";
    }
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    rewind(fp);

    char* data = new char[fsize];
    fread(data, 1, fsize, fp);
    fclose(fp);
    std::string code(data, fsize);
    delete[] data;
    return code;
}

int main(int argc, const char** argv) {
    if(argc != 2) {
        printf("Usage : epScript [input]\n");
        return -1;
    }

    std::string ifname = argv[1];
    std::string ofname = ifname.substr(0, ifname.find_last_of('.')) + ".py";

    std::string code = getFile(argv[1]);
    if(code == "") {
        printf("[Error] File unavailable, or empty file");
        return -2;
    }

    try {
        std::string out = ParseString(code);
        std::ofstream of(ofname);
        of << out << std::endl;
        of.close();
    } catch(std::runtime_error e) {
        printf("Error occured : %s", e.what());
        return -3;
    }
    return 0;
}