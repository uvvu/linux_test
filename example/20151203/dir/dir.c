// ls
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

int main()
{
	struct dirent* p;
	DIR* dp = opendir(".");

	while ((p = readdir(dp)) != NULL)
	{
		printf("%ld %s\n", p->d_ino, p->d_name);
	}

	closedir(dp);
}

