#include "statement.h"
#include <map>
#include "cmd.h"
#include <string>

extern std::map<std::string, cmd_fun> cmdMap;

void init_cmd() {
#ifdef CMD_HELP
    cmdMap.insert(std::make_pair(CMD_HELP, my_help));
#endif
#ifdef CMD_CD
    cmdMap.insert(std::make_pair(CMD_CD, my_cd));
#endif
#ifdef CMD_READ
    cmdMap.insert(std::make_pair(CMD_READ, my_read));
#endif
#ifdef CMD_WRITE
    cmdMap.insert(std::make_pair(CMD_WRITE, my_write));
#endif
#ifdef CMD_CLOSE
    cmdMap.insert(std::make_pair(CMD_CLOSE, my_close));
#endif
#ifdef CMD_OPEN
    cmdMap.insert(std::make_pair(CMD_OPEN, my_open));
#endif
#ifdef CMD_MKDIR
    cmdMap.insert(std::make_pair(CMD_MKDIR, my_mkdir));
#endif
#ifdef CMD_CREATE
    cmdMap.insert(std::make_pair(CMD_CREATE, my_create));
#endif
#ifdef CMD_LS
    cmdMap.insert(std::make_pair(CMD_LS, my_ls));
#endif
#ifdef CMD_EXIT
    cmdMap.insert(std::make_pair(CMD_EXIT, my_exitsys));
#endif
#ifdef CMD_RM
    cmdMap.insert(std::make_pair(CMD_RM, my_rm));
#endif
}