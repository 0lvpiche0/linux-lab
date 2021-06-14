#include <cstring>
#include "statement.h"

extern char *myvhead;
extern DISK *disk;

void my_format() {
    _my_format();
}

void _my_format() {
    free(myvhead);
    memset(myvhead, 0, DISKSIZE);
    disk = (DISK *)myvhead;

    memset(disk, 0, sizeof(DISK));
    for (int i = 0; i < 2; i++) disk->busy[i] = -1; // 最大值
    disk->busy[2] = 2;
    DirFile *dir = (DirFile *) disk->data;
    dir->init(2, 2);
}
