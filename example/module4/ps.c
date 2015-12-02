#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");

// 1. current macro
// 현재 동작하는 프로세스의 ,task_struct 포인터를 얻을 수 있다.


int my_init(void)
{
	struct task_struct *g;
	struct task_struct *t;

	do_each_thread(g, t)
	{
		if (g == t)
			printk("pid = %d, comm = %s\n", g->pid, g->comm);
		else
			printk("\tpid = %d, tid = %d  comm = %s\n", t->pid, t->tgid,  t->comm);
	}
	while_each_thread(g, t);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
}


module_init(my_init);
module_exit(my_exit);


