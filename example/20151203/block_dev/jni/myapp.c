#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int temp;
	int fd = open("/dev/mydev", O_RDWR);


	read(fd, &temp, sizeof(temp));
	printf("temp : %d\n", temp);

	close(fd);
}

