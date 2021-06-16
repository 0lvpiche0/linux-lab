#include "statement.h"

extern DISK* disk;
extern USEROPEN openfilelist[MAXOPENFILE];
extern char* myvhead;
extern bool sys_flag;

void my_exitsys() {
    // printf("it is exitsys\n");
    FILE * fd=fopen("myfsys","w");
    for(int i=1;i<MAXOPENFILE;i++){
        if(openfilelist[i].topenfile==1)
            _my_close(i);
    }
    fwrite(myvhead, sizeof(char), DISKSIZE, fd);
    fclose(fd);
    free(openfilelist->fcb);
    free(myvhead);
    sys_flag = false;
}