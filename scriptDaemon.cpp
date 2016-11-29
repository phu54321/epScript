#include <stdio.h>
#include <io.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "parser/parser.h"

std::string getFile(const std::string& fname);

int daemonTurn(void) {
    _finddatai64_t c_file;
    intptr_t hFile;
    if ( (hFile = _findfirsti64("*.*", &c_file)) != -1L ) {
        do {
            if(c_file.name[0] == '.') continue; // Hidden or . or ..
            if(c_file.attrib & _A_SUBDIR) {
                chdir(c_file.name);
                daemonTurn();
                chdir("..");
            }
            else {
                std::string ifname = c_file.name;
                if(ifname.size() > 4 && ifname.substr(ifname.size() - 4) == ".eps") { // Possible script file
                    std::string ofname = ifname.substr(0, ifname.size() - 4) + ".py";

                    // Check if update is needed
                    bool needUpdating = false;
                    if(access(ofname.c_str(), F_OK) == -1) needUpdating = true;
                    else {
                        struct stat istat, ostat;
                        stat(ifname.c_str(), &istat);
                        stat(ofname.c_str(), &ostat);
                        if (istat.st_mtime > ostat.st_mtime) needUpdating = true;
                    }

                    if(needUpdating) {
                        printf("Updating file %s...\n", c_file.name);
                        std::string out;
                        try {
                            std::string code = getFile(ifname);
                            out = addStubCode(ParseString(code));
                        } catch(std::runtime_error e) {
                            printf("-- Error while parsing file \"%s\" : %s\n", c_file.name, e.what());
                            out = "raise RuntimeError('Compile error')";  // Stub
                        }

                        std::ofstream of(ofname);
                        of << out.c_str() << std::endl;
                        of.close();
                        return 0;
                    }
                }
            }
        } while(_findnexti64(hFile, &c_file) == 0);
        _findclose(hFile);
    }
    return 0;
}

int runDaemon(void) {
    printf("Using daemon mode...\n");
    while(1) {
        daemonTurn();
        sleep(1);
    }
    return 0;
}
