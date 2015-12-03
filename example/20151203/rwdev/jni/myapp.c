#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf;
	int len;
	int fd = open("/dev/mydev", O_RDWR);

	len = read(fd, &buf, sizeof(buf));
	write(1, &buf, len);

	write(fd, &buf, 1);

	close(fd);
}

