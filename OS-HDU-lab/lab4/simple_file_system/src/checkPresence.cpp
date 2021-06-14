#include "statement.h"


int checkPresence(DirFile *dir, bool isFile, const std::string &filename) {
    for (unsigned short i = 0; i < FCBCOUNT; i++) {
        if (dir->fcb[i].in_use && dir->fcb[i].attribute == isFile &&filename == dir->fcb[i].filename) {
            return i;
        } 
    }
    return NOTFOUND;
}