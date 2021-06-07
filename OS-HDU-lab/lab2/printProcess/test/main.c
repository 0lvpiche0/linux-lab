#include <stdio.h>

struct list;
struct list {
    struct list *prev;
    struct list *next;
};

struct A {
    char a,b;
    int c;
    struct list * k;
};

void test1() {
    struct A temp;
    printf("%p\n", &temp);
    printf("%p\n", &temp.k);
    printf("%d", ((int)&((struct A *)0)->k));
}

int main() {
    test1();
    return 0;
}

