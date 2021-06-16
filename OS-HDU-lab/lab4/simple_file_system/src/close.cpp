#include "statement.h"
#include <iostream>
extern USEROPEN openfilelist[MAXOPENFILE];

void my_close() {
    // printf("it is close\n");
    std::string filename;
    std::cin>>filename;
    FCB *fcb = findDirFile(filename, true);
    if (!fcb) printf("no this file\n");
    for (unsigned short i = 0; i < MAXOPENFILE; i++) {
        if (fcb == openfilelist[i].fcb) {
            _my_close(i);
            return ;
        }
    }
    printf("this file is not open\n");
}

void _my_close(unsigned short fd) {
    if (fd >= MAXOPENFILE) return ;
    openfilelist[fd].fcb = NULL;
    openfilelist[fd].dir = "";
    openfilelist[fd].fcbstate = false;
    openfilelist[fd].topenfile = false;
}