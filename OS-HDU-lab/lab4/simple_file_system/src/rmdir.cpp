#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN ptrcuridr; 
extern DISK *disk;
extern std::queue<unsigned short> free_q;

void my_rmdir() {
    std::string str;
    std::cin>>str;
    switch (_my_rmdir(str)) {
    case FAILURE:
        printf("rmdir failure\n");
        break;
    case OK:
        printf("rmdir success\n");
        break;
    default:
        printf("what are you doing\n");
        break;
    }
}

int _my_rmdir(const std::string &dirname) {
    FCB *fcb =  findDirFile(dirname, false);
    if (fcb == NULL) return NOTFOUND;
    DirFile *dir = diskToDir(fcb->first);
    // 检测目录下是否有文件
    bool flag = false;
    for (unsigned short i = 0; i < FCBCOUNT; i++) {
        if (dir->fcb[i].in_use) {
            flag = true;
            break;
        }
    }
    if (flag) {
        printf("There are files in the directory. Do you want to delete them all?\n");
        int input;
        again:
        printf("Please input yes-1 / no-0");
        scanf("%d", &input);
        switch (input) {
        case 0:
            return FAILURE;
        case 1: 
            break;
        default:
            goto again;
        }
    }
    freeDir(dir);
    fcb->in_use = false;
    return OK;
}