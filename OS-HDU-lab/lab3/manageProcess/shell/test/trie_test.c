#include "../lib/trie_node_info.c"
#include "../lib/trie.c"
#include <stdio.h>

int main() {
    struct trie *root= trieInit();
    printf("%d\n",insertNode(root, "cmd1", nodeInitByStr("../task/cmd1")));
    printf("%d\n",insertNode(root, "cmd2", nodeInitByStr("../task/cmd2")));
    printf("%d\n",insertNode(root, "cmd3", nodeInitByStr("../task/cmd3")));
    printTrie(root);
    struct trie_node_info* tmp;
    tmp = findInfo(root, "cmd1");
    if (!tmp) printf("No cmd1\n");
    else printf("%s\n", tmp->path);
    tmp = findInfo(root, "cmd2");
    if (!tmp) printf("No cmd2\n");
    else printf("%s\n", tmp->path);
    tmp = findInfo(root, "cmd3");
    if (!tmp) printf("No cmd3\n");
    else printf("%s\n", tmp->path);
    trieDeleteByPath(root, "cmd2");
    printTrie(root);
    trieDelete(root);
    return 0;
}