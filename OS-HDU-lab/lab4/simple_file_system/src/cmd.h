#ifndef _CMD_H_
#define _CMD_H_


#include <string>

// cmd对应的函数指针
typedef void (*cmd_fun)();
// 将命令初始化加载
void init_cmd(); 

// 命令对应的接口
void my_help();
void _my_help();

// 初始化文件系统
void my_startsys();
// void _my_startsys();
// 格式化系统
void my_format();
void _my_format();
// 打开并读入新的当前目录文件到内存
void my_cd();
void _my_cd(const std::string &dirname);
// 创建目录
void my_mkdir();
void _my_mkdir(const std::string &dirname);
// 删除目录
void my_rmdir();
void _my_rmdir(const std::string &dirname);
// 显示当前目录下的内容
void my_ls();
void _my_ls();
// 创建文件
void my_create();
void _my_create(int fd);
// 删除文件
void my_rm();
void _my_rm(const std::string &filename);
// 打开文件;
void my_open();
void _my_open(const std::string &filename);
// 关闭文件
void my_close();
void _my_close(int fd);
// 写文件
void my_write();
void _my_write(int fd);
// 写入磁盘
int do_write();
int _do_write(const int fd, const std::string &text, const int len, const char wstyle);
// 读文件
void my_read();
void _my_read(int fd, int len);
// 读磁盘文件
int do_read();
int _do_read(int fd, int len, std::string &text);
// 退出
void my_exitsys();
void _my_exitsys();

#endif