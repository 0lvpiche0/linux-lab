#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN ptrcuridr; 
extern DISK *disk;

extern std::queue<unsigned short> free_q;

void my_mkdir() {
    std::string str;
    std::cin>>str;
    switch (_my_mkdir(str)){
    case DIRFULL:
        printf("dir now is full\n");
        break;
    case NOTFREEBLOCK:
        printf("disk is full\n");
        break;
    case EXIST:
        printf("The dir already exists\n");
        break;
    case OK:
        printf("mkdir is ok\n");
        break;
    default:
        printf("wa wa wa wa\n");
        break;
    }
}


int _my_mkdir(const std::string &dirname) {
    auto dir_q = pathSubstr(dirname);
    DirFile *dir;
    if (dir_q.front() == "/") {
        dir = diskToDir(openfilelist->fcb.first);
        dir_q.pop();
    } else {
        dir = diskToDir(ptrcuridr.fcb.first);
    }
    bool flag = false;
    while (!dir_q.empty()) {
        int addr = checkPresence(dir, false, dir_q.front());
        if (addr == NOTFOUND) {
            flag = true;
            int free_addr = findDirFreeAddr(dir);
            if (free_addr == NOTFOUND) return DIRFULL;
            if (free_q.empty()) return NOTFREEBLOCK;
            unsigned short block = free_q.front();
            free_q.pop();
            disk->busy[block] = block;
            dir->fcb[free_addr].init(dir_q.front().c_str(), block, false);
            unsigned short temp = dir->fcb->first;
            dir = diskToDir(block);
            dir->init(temp, block);
        } else {
            dir = diskToDir(dir->fcb[addr].first);
        }
    }
    if (flag) return OK;
    return EXIST;
}