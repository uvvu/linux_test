#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>

#include <asm/uaccess.h>

typedef struct
{
	int data[16];
	int head, tail;

	int size;
	int count;
}QUEUE;

static void init_queue(QUEUE* q)
{
	q->count = 0;
	q->head = q->tail =0;

	q->size = sizeof(q->data) / sizeof(int);
}

static void put(QUEUE* q, int data)
{
	q->data[q->head] = data;
	q->head = (q-> head + 1) % q->size;
	q->count++;
}

static int get(QUEUE* q)
{
	int value = q->data[q->tail];
	q->tail = (q->tail + 1) % q->size;
	q->count--;
}

static int is_empty(QUEUE* q)
{
	return q->count == 0;
}

static int is_full(QUEUE* q)
{
	return q->count == q->size;
}

static QUEUE queue;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

int my_open(struct inode *inode, struct file *file)
{
	printk("my_open()\n");
	init_queue(&queue);
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
	int i, temp;
	if (is_empty(&queue))
		interruptible_sleep_on(&my_wait);

	for (i=0; !is_empty(&queue) 
			&& i < size/sizeof(int);++i)
	{
		temp = get(&queue);
		put_user(temp, (int*)buf + i);
	}

	return i * sizeof(int);
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



irqreturn_t handler(int irq, void *id) 
{
	static int n = 35;
	switch (irq)
	{
		case 379:
			if (!is_full(&queue))
				put(&queue, n++);
			break;

		case 342:
			wake_up_interruptible(&my_wait);
			break;
	}

	return IRQ_HANDLED;
}

static int dev;
int my_init(void)
{
	int ret;
	unsigned long flags =
			IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
		
	printk("my_init()\n");
	misc_register(&misc);

	ret = request_irq(379, handler, flags, "MYIONT", &dev);
	ret = request_irq(342, handler, flags, "MYIONT", &dev);
	
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&misc);

	free_irq(379, &dev);
	free_irq(342, &dev);
}

MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);






