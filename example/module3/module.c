// 모듈 프로그래밍
// => 커널모드에서 개발하기 위한 방법이다.
// 1. 커널을 전체 빌드할 필요가 없다.
// 2. 보드를 재부팅할 필요도 없다.
// 3. 커널을 수정할 필요도 없다.

// init_module : 모듈이 커널에 적재될 때 호출되는 함수
// cleanup_module : 모듈이 커널에서 언로딩 될때 호출

// insmod : 작성된 모듈을 커널에 적재하는 명령어
// lsmod  : 현재 적재된 모듈을 확인하는 명령어

#include <linux/module.h>
#include <linux/kernel.h>

// 모듈에 라이센스를 명시하는 방법.
// 모듈에서 EXPORT_SYMBOL_GPL로 공개된 함수를 호출하는 것이 불가능하다.
// 결국 하드웨어 제어 함수를 호출하는 것이 불가능하다.
MODULE_LICENSE("GPL");

int init_module(void)
{
	printk("init_module\n");
	return 0;
}

void cleanup_module(void)
{
	printk("cleanup_module\n");
}











