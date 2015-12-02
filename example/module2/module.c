#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/init.h> // module_init, module_exit

MODULE_LICENSE("GPL");

// 문제점
// 1. 모듈을 커널에 포함하였을 때, init_module, cleanup_module
//    심볼 충돌이 발생한다. 
// module_init 함수 및 module_exit 함수를 제공하기 때문에 이를 통해 심볼릭 링크의 충돌을 방지할 수 있다.
// 2. 커널에 포함되었을 경우, 부팅시에 init_module이 자동적으로//    호출되어야만 한다.

int my_init(void)
{
	printk("my_init\n");
	return 0;
}

void my_exit(void)
{
	printk("my_exit\n");
}

module_init(my_init);
module_exit(my_exit);











