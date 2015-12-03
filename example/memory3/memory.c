#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/gfp.h>
#include <linux/slab.h>

struct my_struct
{
	char name[20];
	int age;
};

static struct kmem_cache *my_cache;

int my_init(void)
{
	struct my_struct* p;

	my_cache = kmem_cache_create("my_struct", sizeof(struct my_struct), 24,  
			SLAB_HWCACHE_ALIGN | SLAB_POISON, NULL);

	p = kmem_cache_alloc(my_cache, GFP_KERNEL);
	strcpy(p->name, "Tom");
	p->age = 42;

	printk("%s - %d\n", p->name, p->age);
	kmem_cache_free(my_cache, p);

	return 0;
}

void my_exit(void)
{

}



module_init(my_init);
module_exit(my_exit);

