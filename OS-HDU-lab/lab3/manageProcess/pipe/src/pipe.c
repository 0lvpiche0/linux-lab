#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
//This message comes from
#define MAX_CHILD_PROCESS 3
#define READ 0
#define WRITE 1
pid_t pipe_pid = 0;
int pipedes[2];
sem_t *sem_read;
sem_t *sem_write;
void exit_pipe() {
    pid_t this_pid = getpid();
    printf("%d exit\n", this_pid);
    if (pipe_pid == this_pid) {
        sem_close(sem_read);
        sem_close(sem_write);
    }
    exit(0);
}

void init_pipe() {
    sem_read = sem_open("pipe_read",  O_CREAT|O_RDWR, 0644, 0);
    if (sem_read == SEM_FAILED) {
        printf("open_sem read err\n");
        exit_pipe();
    }
    sem_write = sem_open("pipe_write", O_CREAT|O_RDWR, 0644, 1);
    if (sem_write == SEM_FAILED) {
        printf("open_sem write err\n");
        exit_pipe();
    }
    srand((unsigned)time(NULL));
    pipe_pid = getpid();
}

int my_fork(int num) {
    pid_t child_pid = fork();
    if (child_pid < 0) {
        printf("fork error\n");  
        return -1;         
    } else if (child_pid == 0) {
        char buf[1024];
        // "sadadas\0asdasdasd\0sadasd\0"
        sprintf(buf, "This message comes from %d, pid is %d", num, getpid());
        close(pipedes[READ]);
        for (int i = 0; i < num*2; i++) {
            // printf("wait lock num: %d\ti: %d\n",num, i);
            sleep(rand()%3);
            // sem_wait(sem_write);
            // printf("get sem_write\n");
            sleep(rand()%3);
            int status = write(pipedes[WRITE], buf, 1024); 
            if (status == -1) 
                printf("write err\n");
            else 
                printf("writed %d\n", status); 
            // sem_post(sem_write);
            // printf("unlock num: %d\ti: %d\n",num, i);
            sem_post(sem_read);
        }
        exit_pipe();
    }
    return 0;
}

int main() {
    
    init_pipe();
    printf("pipe pid is %d\n", pipe_pid);
    printf("------------------------------------------------------------------------\n");
    //创建信号量
    
    int status = 0;//各类情况的返回值
    int value;
    status = sem_getvalue(sem_write, &value);
    if (status < 0) {
        printf("sem_getvalue sem_write err\n");
        exit_pipe();
    } 
    switch (value) {
    case 0: printf("find sem_write value is 0, and post\n");sem_post(sem_write);break;
    case 1: break;
    default:printf("find sem_write value err\n");exit_pipe();
    }
    status = pipe(pipedes);
    if (status < 0) {
        printf("pipe open error\n");
        exit_pipe();
    }
    pid_t child_pid;
    int count = 0;
    for (int i = 0; i < MAX_CHILD_PROCESS; i++) {
        if (my_fork(i+1) == -1) printf("%d fork erroe\n", i);
        else count += (i+1) * 2;
    }
    for (int i = 0; i < MAX_CHILD_PROCESS; i++) wait(0);
    close(pipedes[WRITE]);
    printf("%d条信息\n", count);
    char buf[1024];
    for (int i = 0; i < count; i++) {
        // printf("parent wait read\n");
        sem_wait(sem_read);
        // printf("parent wait write\n");
        // sem_wait(sem_write);
        int len = read(pipedes[0], buf, 1024);
        printf("read %d", len);    
        // sem_post(sem_write);
        // printf("parent post write\n");
        printf("第%d条信息\n", i+1);
        printf("%s\n", buf);
    }
    exit_pipe();
}