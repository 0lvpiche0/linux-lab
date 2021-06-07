#ifndef _MY_NODE_H_
#define _MY_NODE_H_
struct trie_node_info {
    char *path;
    char *name;
};
//free node
void nodeDelete(struct trie_node_info *p); //necessary

void printInfo(struct trie_node_info *p); //necessary

struct trie_node_info* nodeInitByNode(const struct trie_node_info *info);

/* @s path info */
struct trie_node_info* nodeInitByStr(const char* path, const char *name);
#endif