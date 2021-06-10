#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include "statement.h"
#include "cmd.h"
using namespace std;

// 存储命令
map<string, cmd_fun> cmdMap;
// 系统标志位
bool sys_flag = true;
// 虚拟磁盘起始地址
char *myvhead;


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