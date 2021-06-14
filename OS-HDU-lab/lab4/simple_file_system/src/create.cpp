#include "statement.h"
#include <cstring>
#include <iostream>

extern std::queue<unsigned short> free_q;
extern DISK *disk;

void my_create() {
    std::string str;
    std::cin>>str;
    switch (_my_create(str)) {
    case NOTFOUND:
        printf("path is error\n");
        break;
    case INCORRECT_INPUT:
        printf("your filename is too long\n");
        break;
    case EXIST:
        printf("this file is exist\n");
        break;
    case NOTFREEBLOCK:
        printf("disk is full\n");
        break;
    case OK: 
        break;
    default:
        printf("error\n");
        break;
    }
}

int _my_create(const std::string& filename) {
    auto arr = pathSubstr_2(filename);
    FCB *fcb = findDirFile(arr[0], false);
    if (fcb == NULL) return NOTFOUND;
    if (filename.length() > FILENAME_LEN) return INCORRECT_INPUT;
    DirFile *dir = diskToDir(fcb->first);
    if (checkPresence(dir, true, filename) != NOTFOUND) return EXIST;
    int addr = findDirFreeAddr(dir); 
    if (addr == NOTFOUND) return DIRFULL;
    if (free_q.empty()) return NOTFREEBLOCK;
    unsigned short temp = free_q.front();
    free_q.pop();
    disk->busy[temp] = temp;
    dir->fcb[addr].init(arr[1].c_str(), temp, true);
    return OK;
}
