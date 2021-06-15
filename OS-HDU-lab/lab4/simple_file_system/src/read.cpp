#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;

void my_read() {
    std::string str;
    std::cin>>str;
    int fd = _my_open(str);
    switch (fd) {
    case NOTFOUND:
        printf("can`t find this file\n");
        return ;
    case NO_FREE_OPEN:
        printf("Too many files open\n");
        return ;
    default:
        break;
    }
    printf("How many bytes do you want to read from the file?\n");
    again:
    printf("Or input 0 if you want to read all bytes, input -1 if you don't read\n");
    int len;
    scanf("%d", &len);
    if (len < -1) goto again;
    switch (len) {
    case -1:
        return;
    case 0:
        _my_read(fd, -1);
        return ;
    default:
        _my_read(fd, len);
        return;
    }
}

void _my_read(int fd, unsigned short len) {
    FCB fcb = openfilelist[fd].fcb;
    std::string r_str;
    unsigned short remain_len = fcb.length - openfilelist[fd].count;
    unsigned short r_len = len > remain_len ? remain_len : len;
    _do_read(fd, r_len, r_str);
    std::cout<<r_str<<std::endl;
}


unsigned short _do_read(int fd, unsigned short len, std::string &text) {
    USEROPEN *useropen = &openfilelist[fd];
    if (len > useropen->fcb.length - useropen->count) 
        len = useropen->fcb.length - useropen->count;
    unsigned short res = len;
    unsigned short n = useropen->count / BLOCKSIZE;
    unsigned short m =  useropen->count % BLOCKSIZE;
    unsigned short BlockNum = jumpBlock(useropen->fcb.first, n);
    if (len >= BLOCKSIZE - m) {
        text = std::string{diskToChar(BlockNum) + m, diskToChar(BlockNum + 1)};
        len -= BLOCKSIZE - m;
        useropen->count  += BLOCKSIZE - m;
        BlockNum = jumpBlock(BlockNum, 1); 
    } else {
        text = std::string{diskToChar(BlockNum) + m, diskToChar(BlockNum) + m + len};
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

