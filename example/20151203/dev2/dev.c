#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>
// 문제점
// 1. 드라이버의 메이저 번호가 중복되면 안된다.
// 2. 사용자가 직접 device 특수 파일을 만들어야 한다.
//  mknod mydev c 200 0
// 3. 안드로이드 타겟 보드에서 mknod 명령을 제공하지 않는 경우도 있다.

// => MISC Device Driver
// 1. misc_register, misc_deregister
// 2. MISC_DYNAMIC_MINOR : 자동적으로 마이너번호를 할당.

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
	.release = my_close
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mydev",
	.fops = &fops,
	.mode = 0777
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






