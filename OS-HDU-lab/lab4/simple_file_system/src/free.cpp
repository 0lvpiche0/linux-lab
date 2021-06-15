#include "statement.h"

extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN ptrcuridr; 
extern DISK *disk;
extern std::queue<unsigned short> free_q;

// 释放这一块
inline void freeBlock(unsigned short BlockNum) {
    disk->busy[BlockNum] = 0;
    free_q.push(BlockNum);
}

// 释放该文件指向的磁块，并标注该fcb为未使用
void freeFile(FCB *fcb) {
    unsigned short BlockNum = fcb->first;
    while (disk->busy[BlockNum] != BlockNum) {
        int temp = disk->busy[BlockNum];
        freeBlock(BlockNum);
        BlockNum = temp;
    }
    fcb->first = 0;
    fcb->in_use = false;
    freeBlock(BlockNum);
}

// 释放目录下所有数据包括文件,注意不会将指向该目录的FCB更改
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

// 建议使用，将fcb至于未使用状态，fcb指向的数据释放
void freeFCB(FCB *fcb) {
    switch (fcb->attribute) {
    case true:
        freeFile(fcb);
        break;
    case false:
        freeDir(diskToDir(fcb->first));
        fcb->in_use = false;
    default:
        printf("errrrrr\n");
        return ;
    }
}