#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include <bits/types/time_t.h>
#include <string>
#include <cstring>
#include <ctime>

// 命令
// #define CMD_LEN     16
#define CMD_HELP    "help"
#define CMD_MKDIR   "mkdir"
#define CMD_CD      "cd"
#define CMD_EXIT    "exit"
#define CMD_RM      "rm"
#define CMD_LS      "ls"
#define CMD_OPEN    "open"
#define CMD_CLOSE   "close"
#define CMD_CREATE  "create"
#define CMD_READ    "read"
#define CMD_WRITE   "write"

// 块大小
#define BLOCKSIZE   1024
// 块数量
#define BLOCKCOUNT  1000
// 磁盘大小
const int DISKSIZE = BLOCKSIZE * BLOCKCOUNT;

// 文件名长度
#define FILENAME_LEN 12


struct FCB {
    char filename[FILENAME_LEN]; // 文件名
    char attribute; // 0表示目录，1表示数据文件
    time_t _time; //创建日期
    int first; //起始盘号
    int length; //长度
    int count; //目录项下的文件数量
    FCB(char *str, int _first, char _attribute) {
        strncpy(filename, str, FILENAME_LEN);
        _time = time(NULL);
        first = _first;
        length = 0;
        count = 0;
    }
};

const int FCBCOUNT = BLOCKSIZE / sizeof(FCB);



#endif