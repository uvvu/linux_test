#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/interrupt.h>

// 1. $ cat /proc/interrupts
//  ; 기기에 연결된 인터럽트의 정보를 확인할 수 있다. 

// 2. request_irq / free_irq


// 3. Volume Up에 대한 인터럽트 핸들러도 등록해보세요.

irqreturn_t irq_handler(int irq, void *id)
{
	printk("irq_handler()\n");
	if (irq == 342)
	{
		printk("Volume Down\n");
	}
	else
	{
		printk("Volume Up\n");
	}
	return IRQ_HANDLED;
}

static int my_dev;
int my_init(void)
{
	unsigned long flags = IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	int ret;
	ret = request_irq(342, irq_handler,	flags, "MY_INT", &my_dev);
	ret = request_irq(379, irq_handler, flags, "MY_INT", &my_dev);

	return 0;
}

void my_exit(void)
{
	free_irq(342, &my_dev);
	free_irq(379, &my_dev);
}











module_init(my_init);
module_exit(my_exit);

