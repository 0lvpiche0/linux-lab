#ifndef _MY_TRIE_C_
#define _MY_TRIE_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/trie.h"
#include "../include/trie_node_info.h"



/* 如果在p的子节点里面找不到key（c）则p=NULL,否则返回对应节点 */
#define findKey_from_next(p, c) do { \
    (p) = (p)->children; \
    findKey(p, c) \
} while (0)

#define findKey(p, c) \
    while ((p) && (p)->key != (c)) (p) = (p)->sibling;


struct trie* trieInitByKey(char c) {
    struct trie* tmp = (struct trie*) malloc(sizeof(struct trie));
    tmp->key = c;
    tmp->children = NULL;
    tmp->sibling = NULL;
    return tmp;
}

struct trie* trieInit() {
    struct trie* tmp = (struct trie*) malloc(sizeof(struct trie));
    tmp->key = '\0';
    tmp->children = NULL;
    tmp->sibling = NULL;
    return tmp;
}

void createChild(struct trie *parent, char *path, struct trie_node_info *info) {
    if (parent->children) {
        parent = parent->children;
        while (parent->sibling) parent = parent->sibling;
        parent->sibling = trieInitByKey(*path);
        parent = parent->sibling;
        path++;
    }
    while (*path) {
        parent->children = trieInitByKey(*path);
        parent = parent->children;
        path++;
    }
    parent->info = info;
}


enum RESULT insertNode(struct trie *root, char *path, struct trie_node_info *info) {
    if (!root->children) {
        createChild(root, path, info);
        return SUCCESS;
    }
    struct trie *ptrie = root;
    struct trie *parent;
    while (*path) {
        parent = ptrie;
        findKey_from_next(ptrie, *path);
        if (!ptrie) {
            createChild(parent, path, info);
            return SUCCESS;
        }
        path++;
    }
    if (ptrie->info)  return FAILT;
    ptrie->info = info;
    return SUCCESS;
}

struct trie_node_info* findInfo(struct trie *root, char *path) {
    if (!root) return NULL;
    struct trie *ptrie = root;
    while (*path) {
        findKey_from_next(ptrie, *path);
        if (!ptrie) return NULL;
        path++;
    }  
    return ptrie->info;
}

void dfs_path_print(struct trie *root, char *path, int step) {
    if (!root) return ;
    path[step] = root->key;
    if (root->info) printf("%s\n", path);
    dfs_path_print(root->children, path, step + 1);
    dfs_path_print(root->sibling, path, step);
    path[step] = '\0';
}

void printTrie(struct trie *root) {
    char path[PATH_LEN_MAX];
    memset(path, 0, sizeof(path));
    dfs_path_print(root->children, path, 0);
}

void trieDelete(struct trie *root) {
    if (!root) return ;
    trieDelete(root->children);
    trieDelete(root->sibling);
    nodeDelete(root->info);
    free(root);
}

enum RESULT trieDeleteByPath(struct trie *root, char *path) {
    if (!root) return FAILT;
    struct trie *ptrie = root;
    while (*path) {
        findKey_from_next(ptrie, *path);
        if (!ptrie) return FAILT;
        path++;
    } 
    nodeDelete(ptrie->info);
    ptrie->info = NULL;
    return SUCCESS; 
}

#endif