#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("/dev/mydev", O_RDONLY);
	close(fd);
}

