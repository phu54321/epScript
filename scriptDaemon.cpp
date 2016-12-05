#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include "parser/parser.h"

#ifdef _WIN32
#include <windows.h>
#endif

bool forceUpdate = false;
std::string getFile(const std::string& fname);

int daemonTurn(void) {
    DIR* dp;
    struct dirent* ep;
    struct stat st;

    if ((dp = opendir("./")) != nullptr) {
        while ((ep = readdir (dp)) != nullptr) {
            if(ep->d_name[0] == '.') continue;
            stat(ep->d_name, &st);
            if(S_ISDIR(st.st_mode)) {
                chdir(ep->d_name);
                daemonTurn();
                chdir("..");
            }
            else {
                std::string ifname = ep->d_name;
                if(ifname.size() > 4 && ifname.substr(ifname.size() - 4) == ".eps") { // Possible script file
                    std::string ofname = "_epspy/" + ifname.substr(0, ifname.size() - 4) + ".py";

                    // Check if update is needed
                    bool needUpdating = false;
                    if(forceUpdate) needUpdating = true;
                    else if(access(ofname.c_str(), F_OK) == -1) needUpdating = true;
                    else {
                        struct stat istat, ostat;
                        stat(ifname.c_str(), &istat);
                        stat(ofname.c_str(), &ostat);
                        if (istat.st_mtime > ostat.st_mtime) needUpdating = true;
                    }

                    if(needUpdating) {
                        printf("Updating file %s...\n", ep->d_name);
                        std::string out;
                        try {
                            std::string code = getFile(ifname);
                            out = addStubCode(ParseString(code));
                            mkdir("_epspy");
                            std::ofstream of(ofname);
                            of << out.c_str();
                            of.close();
#ifdef _WIN32
                            if(getParseErrorNum() != 0) {
                                printf("See debugging info\n");
                                SetActiveWindow(GetConsoleWindow());
                                MessageBeep(MB_ICONHAND);
                            }
#endif
                        } catch(std::runtime_error e) {
                            printf("Error occured : %s\n", e.what());
                        }
                    }
                }
            }
        } ;
        closedir(dp);
    }
    return 0;
}

int runDaemon(void) {
    printf("Using daemon mode...\n");
    forceUpdate = true;
    while(1) {
        daemonTurn();
        sleep(1);
        forceUpdate = false;
    }
    return 0;
}
