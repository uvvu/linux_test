//인터럽트

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/timer.h>


MODULE_LICENSE("GPL");

static struct timer_list my_timer;
static void my_handler(unsigned long data)
{
	printk("my_handler()\n");
	//주기적 실행
	mod_timer(&my_timer, jiffies + 5* HZ);
}

int my_init(void)
{
	init_timer(&my_timer);
	my_timer.expires = jiffies + 3 * HZ;
	my_timer.function = my_handler;

	add_timer(&my_timer);
	return 0;
}

void my_exit(void)
{
//	printk("my_exit()\n");
	del_timer(&my_timer);
	printk("Functuion Closed");
}


module_init(my_init);
module_exit(my_exit);


