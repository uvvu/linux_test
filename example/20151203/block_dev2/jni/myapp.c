#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int main()
{
	int ret, i;
	int count;
	int buff[12];
	int fd = open("/dev/mydev", O_RDWR);

	ret = read(fd, buff, sizeof(buff));

	count = ret / sizeof(int);
	for (i = 0 ; i < count ; i++)
		printf("buff[%d] = %d\n", i, buff[i]);


	close(fd);
}

