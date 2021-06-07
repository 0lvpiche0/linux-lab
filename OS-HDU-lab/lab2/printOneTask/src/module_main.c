#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/moduleparam.h>


static pid_t pid = 1;
module_param(pid, int, 0644);

static void print_family(struct task_struct *task) {
    struct list_head *p = NULL;
    struct task_struct *tmp = NULL;
    printk("self:\t%d\t%s\n",task->pid, task->comm);
    if (task->parent) {
        printk("parent:\t%d\t%s\n",task->parent->pid, task->parent->comm);
    } else {
        printk("what?\n");
    }
    //list_for_each(p, &task->sibling) 
    for (p = &task->sibling; p->next != &task->sibling; p = p->next) {
        tmp = list_entry(p, struct task_struct, sibling);
        printk("sibling:\t%d\t%s\n",tmp->pid, tmp->comm);
    }
    list_for_each(p, &task->children) {
        tmp = list_entry(p, struct task_struct, sibling);
        printk("children:\t%d\t%s\n",tmp->pid, tmp->comm);
    }
}

#define ADDR_FOLLOW_PAGE 0xffffffffb3c63f00
static void print_vma_page(struct task_struct *task) {
    struct mm_struct *mm = NULL;
    struct vm_area_struct *vma = NULL;
    //struct page *page = NULL;
    //unsigned long pa;
    int count = 0;
    // struct page * (*follow_page)(struct vm_area_struct *vma, unsigned long address,
	// 		 unsigned int foll_flags) = ADDR_FOLLOW_PAGE;
    //unsigned long start, end, lenth;
    mm = task->mm;
    vma = mm->mmap;
    printk("vma:\tstart\tend\n");
    
    while (vma) {
        
        printk("%6d: %12lu %12lu\n", ++count, vma->vm_start, vma->vm_end);
        //page = follow_page(vma, vma->vm_start, FOLL_GET);
        // if (IS_ERR_OR_NULL(page)) {
        //     printk("err page\n");
        // } else {
        //     printk("vma->start--flags: %lu\n", page->flags);
        // }
        vma = vma->vm_next;
    }
    // pa = pgd_val(*(mm->pgd));
    // printk("page: %ld\n", pa);
    printk("---------------------------------\n");
    
}

static int main_init(void) {
    struct task_struct *task = NULL;
   
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        printk(KERN_ALERT"pid is err\n");
        return -1;
    }
    print_family(task);
    // print_vma_page(task);
    return 0;
}

static void main_exit(void) {
    printk(KERN_ALERT"goodbye!\n");
}

module_init(main_init);  
module_exit(main_exit); 

MODULE_LICENSE("GPL");