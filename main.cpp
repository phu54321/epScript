#include <cstdio>
#include <fstream>
#include <iostream>
#include "parser/tokenAdapter.h"

static std::string get_testdata(std::string dataname) {
    dataname = "../test/testdata/" + dataname;
    FILE* fp = fopen(dataname.c_str(), "rb");
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

#define check(infile, outfile) (ParseString(get_testdata(infile)) == get_testdata(outfile))

int main(int argc, const char** argv) {
    if(argc != 2) {
        printf("Usage : epScript [input]\n");
        return -1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if(fp == nullptr) {
        printf(" - Cannot open file %s\n", argv[1]);
        return -2;
    }
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    rewind(fp);

    char* data = new char[fsize];
    fread(data, 1, fsize, fp);
    fclose(fp);
    std::string code(data, fsize);
    delete[] data;

    try {
        std::string out = ParseString(code);
        std::cout << out << std::endl;
    } catch(std::runtime_error e) {
        printf("Error occured : %s", e.what());
    }
    return 0;
}