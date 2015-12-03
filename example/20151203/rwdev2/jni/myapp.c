#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[16];
	int len;
	int fd = open("/dev/mydev", O_RDWR);

	len = read(fd, &buf, sizeof(buf));
	write(fd, buf, len);

	close(fd);
}

