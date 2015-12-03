
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int n;
	char buf[10];

	int fd1 = open("app2.c", O_RDONLY);
	int fd2 = open("app2.c", O_RDONLY);

	n = read(fd1, buf, sizeof(buf));
	write(1, buf, n);

	n = read(fd2, buf, sizeof(buf));
	write(1, buf, n);
}

