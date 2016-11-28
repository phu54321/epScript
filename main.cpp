#include <cstdio>
#include <fstream>
#include <iostream>
#include "parser/tokenAdapter.h"
#include <unistd.h>

extern bool PARSER_DEBUG;

static std::string getFile(const std::string& fname) {
    FILE* fp = fopen(fname.c_str(), "r");
    if(fp == nullptr) {
        throw std::runtime_error("Input file not found : " + fname);
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

int usage() {
    printf("Usage : epScript [-v] [-o output] input\n");
    printf("Usage : epScript [-v] input1 input2 input3 .. inputN\n");
    return -1;
}

int main(int argc, char** argv) {
    PARSER_DEBUG = false;

    std::string ifname, ofname;
    int param_opt;

    while((param_opt = getopt( argc, argv, "o:v")) != -1)
    {
        switch(param_opt)
        {
            case 'o':
                ofname = optarg;
                break;
            case 'v':
                PARSER_DEBUG = true;
                break;
            case '?':
                return usage();
        }
    }

    if(optind == argc) {  // No input file
        return usage();
    }

    else if(optind < argc - 1 && ofname != "") { // Multiple input files with -o
        return usage();
    }

    if(optind == argc - 1) {
        ifname = argv[optind];
        if(ofname == "") ofname = ifname.substr(0, ifname.find_last_of('.')) + ".py";
        try {
            std::string code = getFile(ifname);
            std::string out = ParseString(code);
            std::ofstream of(ofname);
            of << out << std::endl;
            of.close();
            return 0;
        } catch(std::runtime_error e) {
            printf("Error occured : %s\n", e.what());
            return -2;
        }
    }

    else {
        int totn = argc - optind, succn = 0;
        for(int i = optind; i < argc; i++) {
            ifname = argv[i];
            ofname = ifname.substr(0, ifname.find_last_of('.')) + ".py";
            printf("=== Compiling file %s... ===\n", ifname.c_str());

            try {
                std::string code = getFile(ifname);
                std::string out = ParseString(code);
                std::ofstream of(ofname);
                of << out << std::endl;
                of.close();
                succn++;
            } catch(std::runtime_error e) {
                printf("Error occured : %s\n", e.what());
            }
        }
        printf("=== Compiled %d/%d ===\n", succn, totn);
        return totn - succn;
    }
}