#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
	int df ;
	df = open("text3.txt",O_CREAT,0666);
	printf("%d\n",df);
}
