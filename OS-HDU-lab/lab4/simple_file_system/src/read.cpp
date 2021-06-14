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
    do_read(fd, r_len, r_str);
}



int do_read(int fd, unsigned short len, std::string &text) {
    // unsigned short _n = openfilelist[]
    // char *r = diskToChar(openfilelist[fd].fcb.first);
    // while () {
        
    // }
}

