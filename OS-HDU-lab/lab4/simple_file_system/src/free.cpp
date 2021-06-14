#include "statement.h"

extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN ptrcuridr; 
extern DISK *disk;
extern std::queue<unsigned short> free_q;

inline void freeBlock(unsigned short BlockNum) {
    disk->busy[BlockNum] = 0;
    free_q.push(BlockNum);
}

void freeFile(FCB *fcb) {
    unsigned short BlockNum = fcb->first;
    while (disk->busy[BlockNum] != BlockNum) {
        int temp = disk->busy[BlockNum];
        freeBlock(BlockNum);
        BlockNum = temp;
    }
    freeBlock(BlockNum);
    fcb->in_use = false;
}

void freeDir(DirFile *dir) {
    for (unsigned short i = 0; i < FCBCOUNT; i++) {
        if (dir->fcb[i].in_use)
        switch (dir->fcb[i].attribute) {
        case true:
            freeFile(&(dir->fcb[i]));
            break;
        case false:
            freeDir(diskToDir(dir->fcb[i].first));
            break;
        default:
            printf("wo jue de bu tai keneng\n");
            break;
        }
    }
}