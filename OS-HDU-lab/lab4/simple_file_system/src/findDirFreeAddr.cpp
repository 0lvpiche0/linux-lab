#include "statement.h"

int findDirFreeAddr(DirFile *p) {
    for (unsigned short i = 0; i < FCBCOUNT; i++) {
        if (!p->fcb[i].in_use) return i;
    }
    return NOTFOUND;
}