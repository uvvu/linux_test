#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>

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

ssize_t my_read(struct file *file, 
		char *buf, size_t size, loff_t *off)
{
	char k_buf[] = "Hello";
	int len, ret;

	len = strlen(k_buf);
	len = len > size ? size : len;  
	ret = copy_to_user(buf, k_buf, len);

	// *off += len;

	return len;
}

ssize_t my_write(struct file *file, const char *buf, 
		size_t size, loff_t *off)
{
	int ret;
	char k_buf[16];
	int len = sizeof(k_buf) - 1;

	len = len > size ? size : len;
	k_buf[len] = '\0';

	ret = copy_from_user(k_buf, buf, len);
	printk("k_buf : %s\n", k_buf);
	return len;
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






