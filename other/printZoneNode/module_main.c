#include <linux/mmzone.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>

static int main_init(void) {
    int i;
    pg_data_t *pgdat;
    unsigned long(*kallsyms_lookup_name)(char *name);
    kallsyms_lookup_name = 0xffffffffb15487e0;
    struct pglist_data * (*addr_first) (void) = NULL;
    struct pglist_data * (*addr_next) (struct pglist_data*) = NULL;
    addr_first = kallsyms_lookup_name("first_online_pgdat");
    addr_next = kallsyms_lookup_name("next_online_pgdat");
    printk("goto keyanshijian\n");
    if (!addr_next || !addr_first) {
        printk("寻找失败");
        return 0;
    }
    for (pgdat = addr_first(); pgdat; pgdat = addr_next(pgdat)) {
        printk("node_id is %d\n", pgdat->node_id);
        for (i = 0; i < MAX_NR_ZONES; i++) {
            printk("这是当前node第%d个zone\n", i);
            //struct zone tmp = pgdat->node_zones[i];
            printk("name is %s | start_pfn is %lu\n", pgdat->node_zones[i].name, pgdat->node_zones[i].zone_start_pfn);
        }
    }
    return 0;
}

static void main_exit(void) {
    printk(KERN_ALERT"goodbye!\n");
}

module_init(main_init);  
module_exit(main_exit); 

MODULE_LICENSE("GPL");