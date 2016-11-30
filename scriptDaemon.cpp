#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include "parser/parser.h"


std::string getFile(const std::string& fname);

int daemonTurn(void) {
    DIR* dp;
    struct dirent* ep;

    if ((dp = opendir("./")) != nullptr) {
        while ((ep = readdir (dp)) != nullptr) {
            if(ep->d_type == DT_DIR) {
                chdir(ep->d_name);
                daemonTurn();
                chdir("..");
            }
            else {
                std::string ifname = ep->d_name;
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
                        printf("Updating file %s...\n", ep->d_name);
                        std::string out;
                        try {
                            std::string code = getFile(ifname);
                            out = addStubCode(ParseString(code));
                        } catch(std::runtime_error e) {
                            printf("-- Error while parsing file \"%s\" : %s\n", ep->d_name, e.what());
                            out = "raise RuntimeError('Compile error')";  // Stub
                        }

                        std::ofstream of(ofname);
                        of << out.c_str() << std::endl;
                        of.close();
                        return 0;
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
    while(1) {
        daemonTurn();
        sleep(1);
    }
    return 0;
}
