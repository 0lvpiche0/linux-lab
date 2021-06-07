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
#include "../include/config.h"

sem_t *permision;  
sem_t *full;  
int shmid;

void sender_init() {
    printf("it is sender, pid is %d\n", getpid());
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

void sender_exit() {
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("shmctl(IPC_RMID) failed\n");
        exit(0);
    }
    sem_unlink(permision_name);
    sem_unlink(full_name);
}

int main() {
    sender_init();
    char buf[MAX_SIZE] = {0};
    char *shm = (char *)shmat(shmid, 0, 0);
    if (shm == (void *)-1) {
        printf("shmat failed\n");
        sender_exit();
    }
    printf("input :\n");
    scanf("%s", buf);
    sem_wait(permision);
    strcpy(shm, buf);
    sem_post(full);
    sem_wait(permision);
    printf("sender re: %s\n", shm);
    sender_exit();
}