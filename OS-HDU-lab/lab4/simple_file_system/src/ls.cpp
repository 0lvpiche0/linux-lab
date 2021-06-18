#include "statement.h"
#include <cstdio>

extern USEROPEN ptrcuridr;
extern DISK *disk;

void my_ls() {
    DirFile *dir = diskToDir(ptrcuridr.fcb->first);
    for (unsigned short i = 2; i < FCBCOUNT; i++) {
        if (dir->fcb[i].in_use) 
            printf("%12s", dir->fcb[i].filename);
    }
    printf("\n");
}