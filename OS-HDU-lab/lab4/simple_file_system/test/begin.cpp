#include <iostream>
#include <cstdio>
#include <cstring>

#define BLOCKCOUNT  1024
#define BLOCKSIZE   1024
#define FILE_MAX 16
struct DISK {
    int busy[BLOCKCOUNT]; // 4 * BOCKCOUNT
    char data[BLOCKCOUNT - 4][BLOCKSIZE];//4~1024块存储可以使用
};
char *myvhard;
const int DISKSIZE = BLOCKCOUNT * BLOCKSIZE;

DISK *disk;

void format() {
    memset(myvhard,0,DISKSIZE);
    for(int i = 0;i < 4; i++) {
        disk->busy[i]=1;
    }
}

int main() {
    myvhard=(char *)malloc(DISKSIZE);   //申请1024*1000磁盘空间
    disk=(DISK *)myvhard;
    FILE *fp=fopen("myfsys","r");
    printf("size of bool : %d\n", sizeof(bool));
    printf("size of unsigned short : %d\n", sizeof(unsigned short));
    printf("size of long long : %d\n", sizeof(long long));
    if(fp!=NULL)
    {
        printf("|-------------------------------------------|\n");
        printf("|-----------myfsys is loading---------------|\n");
        printf("|-------------------------------------------|\n\n");
        fread(myvhard,sizeof(char),DISKSIZE,fp);
        fclose(fp);
    }
    else{
        printf("|-------------------------------------------|\n");
        printf("|-----------myfsys is not exit--------------|\n");
        printf("|--File system is being created now --------|\n");
        printf("|-------------------------------------------|\n\n");
        format();
    }
    printf("%d\n", disk->busy[0]);
    FILE *fd=fopen("myfsys","w");
    fwrite(myvhard,sizeof(char),DISKSIZE,fd);
    fclose(fd);
    free(myvhard);
    return 0;
}