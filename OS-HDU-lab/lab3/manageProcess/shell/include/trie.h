#ifndef _MY_TRIE_H_
#define _MY_TRIE_H_

#include <stdlib.h>
#include "trie_node_info.h"

#define PATH_LEN_MAX 30
enum RESULT {SUCCESS, FAILT};


struct trie {
    char key;
    struct trie_node_info* info;
    struct trie* children;
    struct trie* sibling;
};



/* @c 节点关键字 */
struct trie* trieInitByKey(char c);
struct trie* trieInit();

/* 
@root 根
@path  路径
@info 插入的节点信息 
*/
enum RESULT insertNode(struct trie *root, char *path, struct trie_node_info *info);//插入信息

/* 
@path 路径 
@root 根
*/
struct trie_node_info* findInfo(struct trie *root, char *path);

//Delete info by path
enum RESULT trieDeleteByPath(struct trie *root, char *path);

void printTrie(struct trie *root);

void trieDelete(struct trie *root);

#endif