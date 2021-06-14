#include "statement.h"
USEROPEN openfilelist[MAXOPENFILE];

int findFreeOpen() {
    int addr = -1;
    for (unsigned short i = 0; i < MAXOPENFILE; i++) {
        if (!openfilelist[i].topenfile) {
            addr = i;
            break;
        }
    }
    return addr;
}