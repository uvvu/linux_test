#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/gfp.h>
#include <linux/slab.h>

int my_init(void)
{
	char* p;

	p = (char*)kmalloc(GFP_KERNEL, 32);
	printk("p = %p\n", p);

	p[0] = 'a';
	p[32 -1] = 'z';

	printk("%c - %c\n", p[0], p[32 -1]);
	return 0;
}

void my_exit(void)
{

}



module_init(my_init);
module_exit(my_exit);

