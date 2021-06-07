#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>  
#include<semaphore.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <string.h>
#include <sys/msg.h>

#include "../include/config.h"


sem_t *permision;  
sem_t *full;  

int shmid;


void receiver_exit() {
    exit(0);
}

void receiver_init() {
    printf("it is receiver, pid is %d\n", getpid());
    permision = sem_open(permision_name, O_CREAT, 0644, 1);
    if (permision == SEM_FAILED) {
        printf("open sem_permision is err\n");
        exit(0);
    }
    full = sem_open(full_name, O_CREAT, 0644, 0);
    if (full == SEM_FAILED) {
        printf("open sem_full is err\n");
        sem_close(permision);
        exit(0);
    }
    shmid = shmget(KEY_NAME, MAX_SIZE, 0644 | IPC_CREAT);
    if (shmid == -1) {
        printf("shmget failed\\n");
        sem_close(permision);
        sem_close(full);
        exit(0);
    }
}

int main() {
    receiver_init();
    char *shm = (char *)shmat(shmid, 0, 0);
    char buf[MAX_SIZE];
    if (shm == (void *)-1) {
        printf("shmat failed\n");
        receiver_exit();
    }  
    sem_wait(full);
    // strcpy(buf, shm);
    printf("receiver re: %s\n", shm);
    printf("input :\n");
    scanf("%s", buf);
    strcpy(shm, buf);
    sem_post(permision);
    receiver_exit();
}