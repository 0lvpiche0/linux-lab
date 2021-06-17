#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;

void my_read() {
    // printf("it is read\n");
    std::string str;
    std::cin>>str;
    int fd = NOTFOUND;
    FCB *fcb = findDirFile(str, true);
    if (fcb == NULL) {
        printf("can`t find this file\n");
        return ;
    }
    for (unsigned short i = 0; i < MAXOPENFILE; i++) {
        if (openfilelist[i].fcb == fcb) {
            fd = i;
            break;
        }
    }
    switch (fd) {
    case NOTFOUND:
        printf("openlist can`t find this file\n");
        return ;
    default:
        break;
    }
    printf("How many bytes do you want to read from the file?\n");
    int len;
    char wstyle;
    again:
    printf("Or input 0 if you want to read all bytes, input -1 if you don't read\n");
    scanf("%d", &len);
    if (len < -1) goto again;
    wstyle_again:
    switch (len) {
    case -1:
        return;
    case 0:
        printf("Read from head(h) or from the last place(w)\n");
        std::cin>>wstyle;
        if (wstyle != 'h' && wstyle != 'w') goto wstyle_again;
        _my_read(fd, -1, wstyle);
        return ;
    default:
        printf("Read from head(h) or from the last place(w)\n");
        std::cin>>wstyle;
        if (wstyle != 'h' && wstyle != 'w') goto wstyle_again;
        _my_read(fd, len, wstyle);
        return;
    }
}

void _my_read(const unsigned short fd, unsigned short len, const char wstyle) {
    if (fd > MAXOPENFILE) return ;
    FCB *fcb = openfilelist[fd].fcb;
    if (!fcb->attribute) return ;
    std::string r_str;
    unsigned short remain_len = fcb->length - openfilelist[fd].count;
    unsigned short r_len = len > remain_len ? remain_len : len;
    _do_read(fd, r_len, r_str, wstyle);
    std::cout<<r_str<<std::endl;
}


unsigned short _do_read(const unsigned short fd , unsigned short len, std::string &text, const char wstyle) {
    USEROPEN *useropen = &openfilelist[fd];
    // printf("count %d\n", useropen->count);
    // printf("len :%d\n", len);
    unsigned short res = len;
    unsigned short m;
    unsigned short BlockNum;
    switch (wstyle) {
    case 'h':
        BlockNum = useropen->fcb->first;
        if (len > useropen->fcb->length)
            len = useropen->fcb->length;
        m = 0;
        break;
    case 'w':
        m =  useropen->count % BLOCKSIZE;
        BlockNum = jumpBlock(useropen->fcb->first, useropen->count / BLOCKSIZE);
        if (len > useropen->fcb->length - useropen->count) 
            len = useropen->fcb->length - useropen->count;
        break;
    default:
        return 0;
    }
    if (len >= BLOCKSIZE - m) {
        text = std::string{diskToChar(BlockNum) + m, diskToChar(BlockNum + 1)};
        len -= BLOCKSIZE - m;
        useropen->count  += BLOCKSIZE - m;
        BlockNum = jumpBlock(BlockNum, 1); 
    } else {
        text = std::string{diskToChar(BlockNum) + m, diskToChar(BlockNum) + m + len};
        // std::cout<<"m:"<<m<<" len:"<<len<<std::endl;
        useropen->count += len;
        return res;
    }
    while (len - BLOCKSIZE >= 0) {
        text += std::string{diskToChar(BlockNum), diskToChar(BlockNum + 1)};
        useropen->count  += BLOCKSIZE;
        BlockNum = jumpBlock(BlockNum, 1); 
    }
    if (len > 0) {
        text += std::string{diskToChar(BlockNum), diskToChar(BlockNum) + len};
        useropen->count  += len; 
    } 
    return res;
}

