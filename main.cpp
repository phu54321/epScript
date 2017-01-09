#include <cstdio>
#include <fstream>
#include <iostream>
#include "parser/parser.h"
#include "utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#define VERSION "v0.2"

extern bool PARSER_DEBUG;
extern bool MAP_DEBUG;


#ifdef _WIN32
static void mkdir(const char* str, int mode) {
    mkdir(str);
}
#endif

int usage() {
    printf(
            "Basic options\n"
                    "  epScript DIRNAME : Run epScript inside directory as daemon mode.\n"
                    "  epScript [-o output] INPUT : Run epScript for input file.\n"
                    "  epScript INPUT1 INPUT2 INPUT3 ... : Run epScript for multiple files.\n"
                    "Additional options\n"
                    "  -v : Verbose compile. Print debugging informations.\n"
                    "  -d : Debug compile. Map will have debugging informations.\n");
    return -1;
}

int runDaemon(const std::string& dirname);

int main(int argc, char** argv) {
    printf("epScript " VERSION " - eudplib script compiler\n");

    PARSER_DEBUG = false;
    MAP_DEBUG = false;

    std::string ifname, ofname;
    int param_opt;

    while((param_opt = getopt( argc, argv, "o:vd")) != -1)
    {
        switch(param_opt)
        {
            case 'o':
                ofname = optarg;
                break;
            case 'v':
                PARSER_DEBUG = true;
                break;
            case'd':
                MAP_DEBUG = true;
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

        // Run daemon if file is directory
        struct stat st;
        stat(argv[optind], &st);
        if(S_ISDIR(st.st_mode)) {
            return runDaemon(ifname);
        }

        if (ofname == "") {
            // Change extension
            ofname = ifname.substr(0, ifname.find_last_of('.')) + ".py";

            // Add _ prefix
            auto dirs = ofname.find_last_of("\\/");
            if (dirs != std::string::npos) {
                mkdir((ofname.substr(0, dirs) + "/_epspy/").c_str(), 0777);
                ofname = ofname.substr(0, dirs) + "/_epspy/" + ofname.substr(dirs + 1);
            } else {
                mkdir("_epspy", 0777);
                ofname = "_epspy/" + ofname;
            }
        }
        try {
            std::string code = getFile(ifname);
            std::string out = addStubCode(ParseString(ifname, code));
            std::ofstream of(ofname);
            of << out;
            of.close();
            return 0;
        } catch (std::runtime_error e) {
            printf("Error occured : %s\n", e.what());
            return -2;
        }
    }

    else {
        int totn = argc - optind, succn = 0;
        for(int i = optind; i < argc; i++) {
            ifname = argv[i];
            ofname = ifname.substr(0, ifname.find_last_of('.')) + ".py";
            std::string modname;
            printf("=== Compiling file %s... ===\n", ifname.c_str());

            try {
                std::string code = getFile(ifname);
                std::string out = addStubCode(ParseString(ifname, code));
                std::ofstream of(ofname);
                of << out;
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
