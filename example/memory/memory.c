#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/gfp.h>

int my_init(void)
{
	char *p;

	p = (char*)__get_free_pages(GFP_KERNEL, 0);

	printk("p = %p\n", p);
	p[0] = 'a';
	p[4096 - 1] = 'z';

	printk("%c - %c\n", p[0], p[4096 - 1]);
	free_pages(p, 0);
	return 0;
}

void my_exit(void)
{

}



module_init(my_init);
module_exit(my_exit);

