#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>

#include <asm/uaccess.h>

// 1. Blocking 을 사용하는 이유
//  CPU의 자원을 효과적으로 활용하기 위함.
// 2. wait queue는 드라이버에 존재한다.



// 온도.
static int temp = -999;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

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
	if (temp == -999) {
		printk("bloking!!!\n");
		interruptible_sleep_on(&my_wait);
	}

	put_user(temp, (int*)buf);  // temp = *buf;
	return sizeof(temp);
}

static struct file_operations fops = {
	.open = my_open,
	.release = my_close,
	.read = my_read,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mydev",
	.fops = &fops,
};



irqreturn_t sensing(int irq, void *id) 
{
	temp = 37;
	wake_up_interruptible(&my_wait);

	return IRQ_HANDLED;
}

static int dev;
int my_init(void)
{
	int ret;
	printk("my_init()\n");
	misc_register(&misc);

	ret = request_irq(379, sensing, 
			IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			, "MYINT", &dev);

	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&misc);

	free_irq(379, &dev);
}

MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);






