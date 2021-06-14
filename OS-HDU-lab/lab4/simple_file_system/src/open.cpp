#include "statement.h"
#include <iostream>
extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN ptrcuridr; 
extern DISK *disk;
extern std::string currentdir;



void my_open() {
    std::string str;
    std::cin>>str;
    if (str == "") {
        printf("pleas input filename\n");
    }
    switch (_my_open(str)) {
    case -1:
        printf("invalid filename\n");
        break;
    case -2:
        printf("Open file full\n");
    default:
        printf("Open file successfully\n");
        break;
    }
}

int _my_open(const std::string &filename) {
    FCB *fcb = findDirFile(filename, true);
    if (fcb == NULL) return NOTFOUND;
    int fd = findFreeOpen();
    // 找不到空闲的加载
    if (fd == -1) return NO_FREE_OPEN ;
    auto it = filename.end() - 1;
    for (; *it != '/' && it != filename.begin(); it--) ;
    if (filename[0] == '/') openfilelist[fd].init(*fcb, std::string{filename.begin() + 1, filename.end()});
    else openfilelist[fd].init(*fcb, currentdir + std::string{it, filename.end()});
    return fd;
}
