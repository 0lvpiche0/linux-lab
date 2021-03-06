#include "statement.h"
extern USEROPEN ptrcuridr;
extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;;
#include <iostream>

// int findDirFile_F(const std::string &name) {
//     auto q = pathSubstr(name);
//     USEROPEN *p = ptrcuridr;
//     if (q.front() == "/") {
//         p = openfilelist;
//         q.pop();
//     }
//     unsigned short BlockNum = p->fcb.first;
//     std::string temp;
//     while (q.size() != 1) {
//         temp = q.front();
//         q.pop();
//         bool flag = false;
//         DirFile *dir = (DirFile *) disk->data[BlockNum - OFFSET];
//         for (unsigned short i = 0; i < FCBCOUNT; i++) {
//             if (!dir->fcb[i].attribute && temp == dir->fcb[i].filename) {
//                 flag = true;
//                 BlockNum = dir->fcb[i].first;
//             }
//         }
//         if (!flag) return -1;
//     }
//     return BlockNum;
// }

FCB *findDirFile(const std::string &name, bool isFile) {
    
    auto q = pathSubstr(name);
    DirFile *dir = diskToDir(ptrcuridr.fcb->first);
    if (q.front() == "/" || q.front() == "home") {
        q.pop();
        // std::cout<<q.front()<<std::endl;
        if (q.empty()) return openfilelist->fcb;
        dir = diskToDir(openfilelist->fcb->first);
    }
    // unsigned short BlockNum = p->fcb.first;
    std::string temp;
    while (q.size() != 1) {
        // std::cout<<q.front()<<std::endl;
        temp = q.front();
        q.pop();
        bool flag = false;
        for (unsigned short i = 0; i < FCBCOUNT; i++) {
            if (!dir->fcb[i].attribute && temp == dir->fcb[i].filename) {
                flag = true;
                dir = diskToDir(dir->fcb[i].first);
            }
        }
        if (!flag) return NULL;
    }
    int addr = checkPresence(dir, isFile, q.front());
    if (addr != NOTFOUND) return &(dir->fcb[addr]);
    return NULL;
}