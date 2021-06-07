#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <asm/uaccess.h>
//#include <linux/syscall.h>


#define MY_FILE "/home/lpc/MyCode/linux_c/printProcess/log/log.out"

char buf[1024];
struct file *fp = NULL;


static int main_init(void) {
    struct task_struct *p;
    int tmp;
    // mm_segment_t fs;
    // loff_t pos;
    // fp = filp_open(MY_FILE, O_RDWR | O_CREAT, 0644);
    // if (IS_ERR(fp)) {
    //     printk("creat file error\n");
    //     return -1;
    // }
    // fs = get_fs();
    // set_fs(KERNEL_DS);
    // pos = 0;
    
    sprintf(buf, "%s", "类型\t名称\t\t进程号\t状态\t优先级\t父进程号\t组\n");
    // vfs_write(fp, buf, sizeof(buf), &pos);
    printk(KERN_ALERT"%s", buf);

    for_each_process(p) {
        if (p->parent) tmp = p->parent->pid;
        else tmp = -1;
        if (p->mm != NULL) {
            sprintf(buf, "用户进程\t%15s\t%d\t%ld\t%d\t%d\t\t%d\n",p->comm, p->pid, p->state, p->normal_prio, tmp, p->tgid);
        } else {
            sprintf(buf, "内核线程\t%15s\t%d\t%ld\t%d\t%d\t\t%d\n",p->comm, p->pid, p->state, p->normal_prio, tmp, p->tgid);
        }
        // vfs_write(fp, buf, sizeof(buf), &pos);
        printk(KERN_ALERT"%s", buf);
    }
    // filp_close(fp, NULL);
    // set_fs(fs);
    return 0;
}

static void main_exit(void) {
    printk(KERN_ALERT"bye!");
}

module_init(main_init);
module_exit(main_exit);

MODULE_LICENSE("GPL"); 