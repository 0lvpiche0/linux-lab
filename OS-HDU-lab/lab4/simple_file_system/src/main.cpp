#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include "statement.h"
#include "cmd.h"
using namespace std;

// 存储命令
unordered_map<string, cmd_fun> cmdMap;
// 系统标志位
bool sys_flag = true;
// 虚拟磁盘起始地址
char *myvhead;
// 文件打开表
USEROPEN openfilelist[MAXOPENFILE];
// 当前打开文件夹所在位置
USEROPEN ptrcuridr;
queue<unsigned short> free_q;
DISK *disk;
string currentdir;

int main() {
    printf("Welcome the lvpiche FileSystem\n");
    printf("------------------------------\n");
    my_startsys();
    string cmd;
    init_cmd();
    while (sys_flag) {
        cin>>cmd;
        auto &&tmp = cmdMap.find(cmd);
        if (tmp != cmdMap.end()) {
            cmdMap[cmd]();
        } else {
            cout<<"Invalid command, input `help` for more information"<<endl;
        }
    } 
    return 0;
}