#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	int index = 0;
	while(1)	
	{
		fd = open("text3.txt",O_RDONLY);
		if(fd == -1)
		{
			perror("open file error");
			break;
		}

		index++;
	}
	printf("%d\n",index);
	close(fd);
}
