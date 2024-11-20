#include <stdio.h>


int main(int argc , char * argv[])
{
	FILE * fps,*fpc;
	int ch;
	if(argc < 3)
	{
		printf("Usage: %s <src_file><dst_file>\n",argv[0]);
		return -1;
	}
	if ((fps = fopen(argv[1],"r")) == NULL )
	{
		perror("fopen1");
		return -1;
	}
	if((fpc = fopen(argv[2],"w")) == NULL )
	{
		perror("fopen2");
		return -1;
	}
	while((ch = fgetc(fps)) != EOF )
	{
		fputc(ch,fpc);
	}
	fclose(fps);
	fclose(fpc);
	return 0 ;

}
