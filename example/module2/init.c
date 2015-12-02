

#if 0
#define module_init(initfn)					\
	int init_module(void) __attribute__((alias(#initfn)));
module_init(foo);
#endif

#include <stdio.h>

int init_module(void) __attribute__((alias("foo")));

void foo()
{
	printf("foo()\n");
}

int main()
{
	init_module();
}

