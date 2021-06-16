#ifndef _STATEMENT_H_
#define _STATEMENT_H_
# include "cmd.h"
/* lvpiche */

#include <string>
#include <cstring>
#include <ctime>
#include <vector>
#include <queue>
#include <array>

#define NOTFOUND -1
#define NO_FREE_OPEN -2
#define EXIST -3
#define DIRFULL -4
#define NOTFREEBLOCK -5
#define INCORRECT_INPUT -6
#define FAILURE -7
#define OK 0


#define diskToDir(BlocNum) (DirFile *)disk->data[(BlocNum) - OFFSET]
#define diskToFcb(BlocNum) (FCB *) disk->data[(BlocNum) - OFFSET]
#define diskToChar(BlockNum) (char *) disk->data[(BlockNum) - OFFSET]

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
#define BLOCKCOUNT  1024
// 磁盘大小
const int DISKSIZE = BLOCKSIZE * BLOCKCOUNT;
struct FCB;
struct DirFile;
struct USEROPEN;
// 文件名长度
#define FILENAME_LEN 12
#define EXNAME_LEN   4
// 最多打开多少个文件
#define MAXOPENFILE  16

int _my_create(const std::string& filename);

void _my_help();

void _my_startsys();

void _my_format();

int _my_cd(const std::string &dirname);

int _my_mkdir(const std::string &dirname);

int _my_rmdir(const std::string &dirname);

void _my_ls();

int _my_rm(const std::string &filename);

int _my_open(const std::string &filename);

void _my_close(const unsigned short fd);

void _my_write(const unsigned short fd);

unsigned short _do_write(const unsigned short fd, const std::string &text, const char wstyle);

void _my_read(const unsigned short fd, unsigned short len);

unsigned short _do_read(const unsigned short fd, unsigned short len, std::string &text);

void _my_exitsys();

// int open_path(const std::string &path);

// 找到打开列表里面空闲的位置
int findFreeOpen();

// 检测是否dir已存在该目录或文件
int checkPresence(DirFile *dir, bool isFile, const std::string &filename);

// 找该目录下空闲的FCB
int findDirFreeAddr(DirFile *p);

// 将路径切割用队列保存
std::queue<std::string> pathSubstr(const std::string &path);
// 返回该路径下的目录路径和文件名
std::array<std::string, 2> pathSubstr_2(const std::string &path);

// 返回文件名和文件扩展名
// std::array<std::string, 2> getFileName(const std::string &filename);

// 找到目录或者文件，找不到返回NULL，找到返回FCB
FCB *findDirFile(const std::string &name, bool isFile);
// int findDirFile_F(const std::string &name);

// 从BlockNum开始跳转n次
unsigned short jumpBlock(unsigned short BlockNum, int n);

void freeBlock(unsigned short BlockNum);

void freeFile(FCB *fcb);

void freeDir(DirFile *dir);

// 文件描述块，如FILENAME_LEN为12则刚好能划分1024为32块
struct FCB {
    char filename[FILENAME_LEN]; // 文件名
    // char exname[EXNAME_LEN]; // 文件扩展名
    bool attribute; // false表示目录，true表示数据文件
    time_t _time; //创建日期
    unsigned short first; //起始盘号
    unsigned int length; //长度
    bool in_use; // 是否为空
    void init(const char *str, unsigned int _first, bool _attribute) {
        strncpy(filename, str, FILENAME_LEN);
        _time = time(NULL);
        first = _first;
        length = 0;
        attribute = _attribute;
        in_use = true;
    }
};

const int FCBSIZE = sizeof(FCB);
const int FCBCOUNT = BLOCKSIZE / FCBSIZE;

// 目录
struct DirFile {
    FCB fcb[FCBCOUNT];  //一个目录下最多 FCBCOUNT - 2个FCB
    void init(int father,int self) {
        //给根目录创建.. 和 .  序号0放".", 序号1放".."
        memset(fcb,0,sizeof(fcb));
        fcb[1].in_use=fcb[0].in_use=true;
        fcb[1].attribute=fcb[0].attribute=false;
        fcb[1].first=father;
        fcb[0].first=self;
        memcpy(fcb[0].filename, ".",sizeof("."));
        memcpy(fcb[1].filename, "..",sizeof(".."));
    }
};

typedef unsigned short busy_t;
const unsigned short OFFSET = sizeof(busy_t);
struct DISK {
    busy_t busy[BLOCKCOUNT]; // OFFSET * BOCKCOUNT   0为空闲 其他是指向下标表示块号
    char data[BLOCKCOUNT - OFFSET][BLOCKSIZE];//2~1024块存储可以使用
};

struct USEROPEN {
    FCB *fcb;
    std::string dir;//相应打开文件所在的目录名
    unsigned short count;//读写指针在文件的位置
    bool fcbstate;//是否修改了文件的FCB内容，修改了置为1,否则置为0
    bool topenfile;//表示是否打开表项，true就是被占用,false就是没有被占用
    void init(FCB *fcb, const std::string &dir) {
        this->fcb = fcb;
        this->dir = dir;
        count = 0;
        fcbstate = false;
        topenfile = true;
    }
};


#endif