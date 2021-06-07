#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define KEY_VAL 8848
#define MAX_MESSAGE 1024
// sem_t *sem_write;
sem_t *io_mutex;//标准IO
sem_t *sem_arg;
sem_t *sem_read; //判断是否有东西读
pthread_t pt[3];

int *arg;
int msgid;
int key;

struct msgbuf {
    long mtype; /* 消息类型，必须 > 0 */
    char mtext[MAX_MESSAGE]; /* 消息文本 */
};


void *sender(void *args) {
    int thread_arg = *((int *)args);
    sem_post(sem_arg);
    char thread_info_input[MAX_MESSAGE];
    char thread_info_write[MAX_MESSAGE];
    struct msgbuf msg;
    msg.mtype = 3;
    sprintf(thread_info_input, "it is %d thread", thread_arg);

    char exit_info[10];
    sprintf(exit_info, "end%d", thread_arg);
    int flag = 1;
    while (flag) {
        sem_wait(io_mutex);
        printf("%s\t, please input message(len less 1024):\n", thread_info_input);
        char message[MAX_MESSAGE];
        scanf("%s", message);
        sem_post(io_mutex);
        if (strcmp(message, "exit") == 0) {
            // msg.mtype = 2;
            strcpy(msg.mtext, exit_info);
            flag = 0;
        } else {
            strcpy(msg.mtext,message);
        }
        msgsnd(msgid, &msg, sizeof(message), 0);
        // sem_post(sem_read);
        // sprintf(thread_info_write, "%s, write: %s",thread_info_input, msg.mtext);
        // sem_wait(io_mutex);
        // printf("%s\n", thread_info_write);
        // sem_post(io_mutex);
    }
    // memset(msg.mtext, 0, sizeof(msg.mtext));
    sem_wait(io_mutex);
    msgrcv(msgid,&msg,MAX_MESSAGE,thread_arg,0);
    printf("%s, receive %s, exit\n", thread_info_input, msg.mtext );
    sem_post(io_mutex);
    exit(0);
}

void *receiver(void *args) {
    // printf("create receiver\n");
    int thread_arg = *((int *)args);
    sem_post(sem_arg);
    struct msgbuf msg;
    msg.mtype = 4;
    char thread_info[MAX_MESSAGE];
    sprintf(thread_info, "it is %d thread, get message: ", thread_arg);
    int count = 0;
    int i;
    while (count < 2) {
        i++;
        char message[MAX_MESSAGE];
        msgrcv(msgid, &msg, MAX_MESSAGE, 3, 0);
        if (!strcmp(msg.mtext, "end1") || !strcmp(msg.mtext, "end2")) {
            char c = msg.mtext[3];
            count++;
            sprintf(msg.mtext, "over%c", c);
            msg.mtype = c - '0';
            msgsnd(msgid, &msg, sizeof(message), 0);
        } else {
            sem_wait(io_mutex);
            printf("it is %d message\n%s %s\n",i, thread_info, msg.mtext);
            sem_post(io_mutex);
        }
    }
    exit(0);
}

void message_queue_init() {
    printf("begin init\n");
    io_mutex = (sem_t *) malloc(sizeof(sem_t));
    sem_arg = (sem_t *) malloc(sizeof(sem_t));
    sem_init(io_mutex, 0, 1);
    // sem_init(sem_write, 0, 1);
    sem_init(sem_arg, 0, 1);
    // sem_init(sem_read, 0, 0);
    arg = malloc(sizeof(int));
    key = KEY_VAL;
    msgid = msgget(key, IPC_CREAT | 0666 );
    if (msgid == -1) {
        printf("Create Message Queue Error\n");
        exit(0);
    }
    printf("pid is %d, init\n", getpid());
}

void message_queue_exit() {
    printf("Main exit\n");
    free(io_mutex);
    free(sem_arg);
    free(arg);
    exit(0);
}

int main() {
    message_queue_init();
    for (int i = 0; i < 2; i++) {
        sem_wait(sem_arg);
        *arg = i + 1;
        pthread_create(pt + i, NULL, sender, arg);
    }
    // sem_wait(io_mutex);
    // printf("sender is ok\n");
    // sem_post(io_mutex);
    sem_wait(sem_arg);
    *arg = 3;
    pthread_create(pt + 2, NULL, receiver, arg);
    for (int i = 0; i < 3; i++) pthread_join(pt[i], NULL);
    message_queue_exit();
}