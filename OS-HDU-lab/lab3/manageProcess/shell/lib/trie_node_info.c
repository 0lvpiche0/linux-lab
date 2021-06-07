#ifndef _MY_NODE_C_
#define _MY_NODE_C_

#include "../include/trie_node_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie_node_info* nodeInitByStr(const char* path, const char *name) {
    struct trie_node_info *res = (struct trie_node_info *) malloc(sizeof(struct trie_node_info));
    char *s = (char *) malloc((strlen(path) + 1) * sizeof(char));
    strcpy(s, path);
    char *s2 = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(s2, name);
    res->path = s;
    res->name = s2;
    return res;
}

struct trie_node_info* nodeInitByNode(const struct trie_node_info *info) {
    return nodeInitByStr(info->path, info->name);
}

void nodeDelete(struct trie_node_info *p) {
    if (!p) return ;
    free(p->path);
    free(p);
}

#endif