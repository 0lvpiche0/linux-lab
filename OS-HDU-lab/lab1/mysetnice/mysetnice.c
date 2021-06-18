SYSCALL_DEFINE5(mysetnice, pid_t, pid, int, flag, int, niceval, void __user *, prio, void __user *, nice) {
	struct task_struct* task = NULL;
	int nicebef;
	int priobef;
	task = find_get_task_by_vpid(pid);
	if (!task) return EFAULT;
	nicebef = task_nice(task);
	priobef = task_prio(task);
	switch (flag) {
		case 0 :
			if(copy_to_user(nice, &nicebef, sizeof(nicebef))) return EFAULT;
			if(copy_to_user(prio, &priobef, sizeof(priobef))) return EFAULT;
			printk("nice: %d | prio: %d\n", nicebef, priobef);
			return 0;
		case 1 : 
			printk("oldnice: %d | newnice: %d\n", nicebef, niceval);
			set_user_nice(task, niceval);
			nicebef = task_nice(task);
			priobef = task_prio(task);
			if(copy_to_user(nice, &nicebef, sizeof(nicebef))) return EFAULT;
			if(copy_to_user(prio, &priobef, sizeof(priobef))) return EFAULT;
			return 0;
		default :
			printk("flag is error\n");
	}
	return EFAULT;
}