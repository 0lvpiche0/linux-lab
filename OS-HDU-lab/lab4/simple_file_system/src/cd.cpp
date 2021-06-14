#include "statement.h"
#include <iostream>

extern USEROPEN ptrcuridr;;  
extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;
extern std::string currentdir;;

void my_cd() {
    std::string str;
    std::cin>>str;
    switch (_my_cd(str)) {
    case NOTFOUND:
        printf("can`t find this dir\n");
        break;
    case OK:
        printf("cd is okkkk\n");
        break;
    default:
        printf("wa zheli youge error\n");
        break;
    }
}

// 完成
int _my_cd(const std::string &dirname) {
    auto arr = pathSubstr_2(dirname);
    FCB *fcb = findDirFile(dirname, false);
    if (fcb == NULL) return NOTFOUND;
    if (dirname[0] == '/') {
        currentdir = std::string{dirname.begin() + 1, dirname.end()};
    } else {
        currentdir += dirname;
    }
    ptrcuridr.fcb = *fcb;
    ptrcuridr.dir = currentdir;
    return OK;
}