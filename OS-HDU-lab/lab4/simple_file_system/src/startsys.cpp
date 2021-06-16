#include <statement.h>
#include <queue>

extern void _my_format();
extern char *myvhead;
extern DISK *disk;
extern USEROPEN openfilelist[MAXOPENFILE];
extern USEROPEN *ptrcuridr;
extern std::queue<unsigned short> free_q;

void mount_home() {
    memset(openfilelist,0,sizeof(openfilelist));
    openfilelist->fcb = new FCB;
    openfilelist->fcb->first = 2;
    openfilelist->topenfile = true;
    strcpy(openfilelist->fcb->filename, "home");
    openfilelist->fcb->attribute = false;
    openfilelist->fcb->in_use = true;

}

void my_startsys() {
    _my_startsys();
}

void _my_startsys() {
    myvhead = (char *)malloc(DISKSIZE);   //申请1024*1024磁盘空间
    disk = (DISK *)myvhead;
    FILE *fp = fopen("myfsys","r");
    if(fp!=NULL) {
        printf("|-------------------------------------------|\n");
        printf("|------------------loading------------------|\n");
        printf("|-------------------------------------------|\n\n");
        fread(myvhead,sizeof(char),DISKSIZE,fp);
        fclose(fp);
    } else {
        printf("|-------------------------------------------|\n");
        printf("|-----------disk is not exit----------------|\n");
        printf("|-----File system is being created now -----|\n");
        printf("|-------------------------------------------|\n\n");
        _my_format();
    }
    mount_home();
    // 初始化空闲块队列
    for (size_t i = 0; i < BLOCKCOUNT; i++) 
        if (!disk->busy[i]) free_q.push(i);
    ptrcuridr = openfilelist;
    printf("The file system has been loaded, please input the command\n");
}