#ifndef _CMD_H_
#define _CMD_H_


#include <string>

// cmd对应的函数指针
typedef void (*cmd_fun)();
// 将命令初始化加载
void init_cmd(); 

// 命令对应的接口
void my_help();


// 初始化文件系统
void my_startsys();

// void _my_startsys();
// 格式化系统
void my_format();

// 打开并读入新的当前目录文件到内存
void my_cd();

// 创建目录
void my_mkdir();

// 删除目录
void my_rmdir();

// 显示当前目录下的内容
void my_ls();

// 创建文件
void my_create();

// 删除文件
void my_rm();

// 打开文件;
void my_open();

// 关闭文件
void my_close();

// 写文件
void my_write();

// 写入磁盘
int do_write();

// 读文件
void my_read();

// 读磁盘文件
void do_read();

// 退出
void my_exitsys();


#endif