#include "statement.h"
#include <iostream>

int checkPresence(DirFile *dir, bool isFile, const std::string &filename) {
    // std::cout<<filename<<std::endl;
    for (unsigned short i = 0; i < FCBCOUNT; i++) {
        // std::cout<<dir->fcb[i].filename<<std::endl;
        if (dir->fcb[i].in_use && dir->fcb[i].attribute == isFile &&filename == dir->fcb[i].filename) {
            return i;
        } 
    }
    return NOTFOUND;
}