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
        unsigned short temp = disk->busy[BlockNum];
        freeBlock(BlockNum);
        BlockNum = temp;
    }
    freeBlock(BlockNum);
    fcb->first = 0;
    fcb->in_use = false;
}

// 释放目录下所有数据包括文件,注意不会将指向该目录的FCB更改
void freeDir(DirFile *dir) {
    for (unsigned short i = 2; i < FCBCOUNT; i++) {
        if (dir->fcb[i].in_use)
        if (dir->fcb[i].attribute) {
            freeFile(&(dir->fcb[i]));
        } else {
            freeDir(diskToDir(dir->fcb[i].first));
        }      
    }
}

// 建议使用，将fcb至于未使用状态，fcb指向的数据释放
void freeFCB(FCB *fcb) {
    if (fcb->in_use)
    if (fcb->attribute) {
        freeFile(fcb);
    } else {
        freeDir(diskToDir(fcb->first));
    }  
}