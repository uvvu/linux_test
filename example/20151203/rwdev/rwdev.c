#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>

ssize_t my_read(struct file *file, char *buf, size_t size, loff_t *off)
{
	printk("my_read()\n");

	put_user('A', buf);

	return 1;
}

ssize_t my_write(struct file *file, const char *buf, size_t size, loff_t *off)
{
	printk("my_write()\n");
	char k_buf;

	get_user(k_buf, buf);

	printk("my_buf : %c", k_buf);

	return 1;
}

int my_open(struct inode *inode, struct file *file)
{
	printk("my_open()\n");
	return 0;
}

int my_close(struct inode *inode, struct file *file)
{
	printk("my_close()\n");
	return 0;
}

static struct file_operations fops = {
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mydev",
	.fops = &fops,
};

int my_init(void)
{
	printk("my_init()\n");
	misc_register(&misc);

	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&misc);
}

MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);






