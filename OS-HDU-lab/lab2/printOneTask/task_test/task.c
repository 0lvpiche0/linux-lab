#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <linux/sched.h>
//#include <linux/mm.h>

// void fun(struct task_struct *task) {
//     struct mm_struct *mm = NULL;
//     struct vm_area_struct *vma = NULL;
//     int count = 0;
//     mm = task->mm;
//     vma = mm->mmap;
//     printf("vma:\tstart\tend\n");
//     while (vma) {
//         printf("%6d: %12lu %12lu\n", ++count, vma->vm_start, vma->vm_end);
//         vma = vma->vm_next;
//     }
// }

int main() {
    int x;
    int i;
    int *m = NULL;
    pid_t pid = getpid();
    struct task_struct *task = NULL;
    //task = pid_task(find_vpid(pid), PIDTYPE_PID);
    printf("PID is %d\n-----------------------------------------\n", pid);
    while (scanf("%d", &x) != EOF) {
        m = (int *) malloc(sizeof(int)*x);
        //fun(task);
        printf("<<<<<<<<<<<\n");
        for (i = 0; i < x; i++) m[i] = 1;
        //fun(task);
        printf(">>>>>>>>>>>\n");
    }
    return 0;
}