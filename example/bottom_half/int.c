#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/interrupt.h>
#include <linux/workqueue.h>

// 1. $ cat /proc/interrupts
//  ; 기기에 연결된 인터럽트의 정보를 확인할 수 있다. 

// 2. request_irq / free_irq


// 3. Volume Up에 대한 인터럽트 핸들러도 등록해보세요.

//		Top Haf : ISR
//		; 신속하게 처리되어야 하는 작업, 하드웨어 초기화, 에코
// 4. Bottm Haf : workqueue
//		; 추후 처리되도 되는 부분, 메모리 복제, 복잡한 계산 등

static int my_dev;
static struct work_struct my_work;
irqreturn_t irq_handler(int irq, void *id)
{
	if (irq == 342)
	{
		printk("Volume Down\n");
	}
	else
	{
		printk("Volume Up\n");
	}

	schedule_work(&my_work);


	return IRQ_HANDLED;
}

void my_work_handler(struct work_struct* work)
{
	printk("my_work_handler()\n");
}


int my_init(void)
{
	unsigned long flags = IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	int ret;
	ret = request_irq(342, irq_handler,	flags, "MY_INT", &my_dev);
	ret = request_irq(379, irq_handler, flags, "MY_INT", &my_dev);

	INIT_WORK(&my_work, my_work_handler);

	return 0;
}

void my_exit(void)
{
	free_irq(342, &my_dev);
	free_irq(379, &my_dev);
}










module_init(my_init);
module_exit(my_exit);

