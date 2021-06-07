#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define R_MAX_LEN 1024 * 500
#define W_MAX_LEN 1024 * 50
#define W_LEN 1024
int fd[2];
void err_exit(const char *s) {
    printf("%s err\n", s);
    exit(0);
}

void my_fork1(int i) {
    
    if (fork() == 0) {
        char buf[W_MAX_LEN];
        memset(buf, 0, sizeof(buf));
        for (int j = 0; j < W_MAX_LEN - 1; j++) buf[j] = 'a' + i;
        //buf[MAX_LEN - 1] = '\0'; 
        int j = 0;
        while (j++ < 100000) {
            int len = write(fd[1], buf, sizeof(buf));
            // printf("writen buf %d\n", len);
        } 
        exit(0);
    } 
    return ;
    
}

void my_fork2(int i) {
    if (fork() == 0) {
        char buf[W_LEN];
        memset(buf, 0, sizeof(buf));
        for (int j = 0; j < W_LEN - 1; j++) buf[j] = 'a' + i;
        //buf[MAX_LEN - 1] = '\0'; 
        int j = 0;
        while (j++ < 100000) {
            int len = write(fd[1], buf, sizeof(buf));
            // printf("writen buf %d\n", len);
        } 
        exit(0);
    } 
    return ;
}

int main() {
    int status;
    char buf[R_MAX_LEN];
    int count = 0;
    status = pipe(fd);
    if (status < 0) err_exit("pipe open");
    int ch;
    scanf("%d", &ch);
    //my_fork1(1);
    my_fork2(0);
    while (1) {
        sleep(1);
        int len = read(fd[0], buf, sizeof(buf));
        if (len % 1024) 
            printf("err read %d\n", len);
        else 
            printf("%d\tread %d\n",++count, len);
            
        //printf("%s\n", buf);
    }
}