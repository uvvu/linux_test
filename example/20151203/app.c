#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	pid_t pid = fork();
	char buf;
	int fd = open("app.c", O_RDONLY);
	printf("fd : %d\n", fd);

	read(fd, &buf, sizeof(buf));
	write(STDOUT_FILENO, &buf, 1);

	read(fd, &buf, sizeof(buf));
	write(STDOUT_FILENO, &buf, 1);
	
	if (pid == 0) 
	{
		read(fd, &buf, sizeof(buf));
		write(STDOUT_FILENO, &buf, 1);
	}



	return 0;
}

// 0 : stdin
// 1 : stdout - line buffering
// 2 : stderr - non buffering

