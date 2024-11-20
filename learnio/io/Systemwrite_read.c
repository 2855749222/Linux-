#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main()
{
	int fd;
	fd = open("text1.txt",O_RDWR,0644);
	if(fd == -1)
	{
		perror("open:arror");
	}
	char but[10] = {0};
	int n = 0;
	int fd2;
	fd2 = open("text3.txt",O_RDWR,0644);
	if(fd2 == -1)
	{
		perror("open2:arror");
	}
	while(1)
	{
		n = read(fd,but,10);
		if(n == 0)
		{
			break;
		}
		write(fd2,but,strlen(but));

	}
	close(fd);
	close(fd2);	
}
