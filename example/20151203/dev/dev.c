#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>

// 1. 드라이버 등록 함수 : register_chrdev
// 2. 드리이버 등록 해지 함수 :  unregister_chrdev
// 3. 디바이스 목록 확인(maje 번호 겹치지 않도록 cat /proc/devices)

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

static struct file_operations fops = 
{
	.open = my_open,
		.release = my_close
};

MODULE_LICENSE("GPL");

int my_init(void)
{
	printk("my_init()\n");

	register_chrdev(200, "MY_DEV_DRIVER", &fops);
	return 0;

}

void my_exit(void)
{
	printk("my_exit()\n");
}

module_init(my_init);
module_exit(my_exit);


