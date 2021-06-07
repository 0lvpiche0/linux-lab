#include "../include/trie_node_info.h"
#include "../include/trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

struct trie *root;
pid_t shell_pid = 0;


void exit_shell() {
    trieDelete(root);
    exit(0);
}

int shell_fork(const char *path, const char *name) {
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (!pid) {
        if (execl(path, name, NULL) < 0) return -2;
        exit(0);
    } 
    return pid;
}

void init_shell() {
    root = trieInit();
    shell_pid = getpid();
}

int main() {
    init_shell();
    printf("shell pid is %d\n", shell_pid);
    printf("------------------------------------------------------------------------\n");
    int err = 0;
    //预加载命令
    err += insertNode(root, "cmd1", nodeInitByStr("./task/cmd1", "cmd1"));
    err += insertNode(root, "cmd2", nodeInitByStr("./task/cmd2", "cmd2"));
    err += insertNode(root, "cmd3", nodeInitByStr("./task/cmd3", "cmd3"));
    if (err > 0) {
        printf("共有%d个error\n", err);
        exit_shell();
        return 0;
    }
    char path[PATH_LEN_MAX];
    struct trie_node_info *info = NULL;
    while (scanf("%s", path) != EOF) {
        info = findInfo(root, path);
        switch ((unsigned long)info) {
        case 0: 
            printf("No this cmd\n"); 
            break;
        default:
            err = shell_fork(info->path, info->name);
            switch (err) {
            case -1: printf("fork err\n");break;
            case -2: printf("execl err\n");break;
            default: break;
            }
            break;
        }
    }
    exit_shell();
}