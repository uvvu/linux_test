#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h> // for using struct task_struct


MODULE_LICENSE("GPL");

// 1. current macro
// 현재 동작하는 프로세스의 ,task_struct 포인터를 얻을 수 있다.


int my_init(void)
{
	struct task_struct* p;

	for_each_process(p)
	{
		printk("pid = %d, comm = %s\n", p->pid, p->comm);
	}

	return 0;
}
#if 0
int my_init(void)
{
	struct task_struct* p = current;
	struct task_struct* t;
	struct list_head* temp;

	temp = p->tasks.next;
	while (temp != &p->tasks)
	{
		t = list_entry(temp, struct task_struct, tasks);
		printk("pid = %d, comm = %s\n", t->pid, t->comm);
		temp = temp->next;
	}
	t = list_entry(temp, struct task_struct, tasks);
	printk("pid = %d, comm = %s\n", t->pid, t->comm);
	
	return 0;
}
#endif 

#if 0
int my_init(void)
{
	struct task_struct* p = current;
	printk("my_init()\n");
	printk("pid = %d, comm = %s\n",p->pid, p->comm);

	return 0;
}
#endif 

void my_exit(void)
{
	printk("my_exit()\n");
}


module_init(my_init);
module_exit(my_exit);


