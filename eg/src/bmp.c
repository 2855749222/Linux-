#include "bmp.h"
#include "lcd.h"

//显示图片
int bmp_show(const char *bmpFile,int posX,int posY)
{
    //打开bmp文件
    int bmpFd = open(bmpFile,O_RDONLY);
    if(bmpFd == -1)
    {
        log_error("open bmp error");
        return -1;
    }

    struct tagBITMAPFILEHEADER bfh;
    read(bmpFd,&bfh,sizeof(bfh));
    struct tagBITMAPINFOHEADER bih;
    read(bmpFd,&bih,sizeof(bih));

    int bmpWidth = bih.biWidth;
    int bmpHeight = bih.biHeight;

    if(bmpWidth % 4 != 0)
    {
        log_error("image width is not a multiple of 4");
        return -1;
    }

    char bmpBuf[bmpWidth * bmpHeight * 3];
    memset(bmpBuf,0,bmpWidth * bmpHeight * 3);

    int tempBuf[bmpHeight][bmpWidth];
    memset(*tempBuf,0,bmpWidth * bmpHeight * 3);

    //从bmp中读取数据
    read(bmpFd,bmpBuf,bmpWidth * bmpHeight * 3);

    for(int i = 0,j = 0; i < bmpWidth * bmpHeight; i++,j+=3)
    {
        (*tempBuf)[i] = 0x00 << 24 | bmpBuf[j + 2] << 16 | bmpBuf[j + 1] << 8 | bmpBuf[j];
    }

    //把处理后的图像数据存到lcd虚拟内存
    for(int row = 0; row < bmpHeight; row++)
    {
        for(int column = 0; column < bmpWidth; column++)
        {
            lcdBuf[row + posY][column + posX] = tempBuf[bmpHeight - row][column];
        }
    }

	close(bmpFd);

	log_debug("show %s completed",bmpFile);
}

//按倍率显示图片
int bmp_showScale(const char *bmpFile,int posX,int posY,int scale)
{
    //打开bmp文件
    int bmpFd = open(bmpFile,O_RDONLY);
    if(bmpFd == -1)
    {
        log_error("open bmp error");
        return -1;
    }

    struct tagBITMAPFILEHEADER bfh;
    read(bmpFd,&bfh,sizeof(bfh));
    struct tagBITMAPINFOHEADER bih;
    read(bmpFd,&bih,sizeof(bih));

    int bmpWidth = bih.biWidth;
    int bmpHeight = bih.biHeight;

    if(bih.biWidth % 4 != 0)
    {
        log_error("image width is not a multiple of 4");
        return -1;
    }

    char bmpBuf[bmpWidth * bmpHeight * 3];
    memset(bmpBuf,0,bmpWidth * bmpHeight * 3);

    int tempBuf[bmpHeight][bmpWidth];
    memset(*tempBuf,0,bmpWidth * bmpHeight * 3);

    //从bmp中读取数据
    read(bmpFd,bmpBuf,bmpWidth * bmpHeight * 3);

    for(int i = 0,j = 0; i < bmpWidth * bmpHeight; i++,j+=3)
    {
        (*tempBuf)[i] = 0x00 << 24 | bmpBuf[j + 2] << 16 | bmpBuf[j + 1] << 8 | bmpBuf[j];
    }

    int scaleWidth,scaleHeight;
    scaleWidth = bmpWidth / scale;
    scaleHeight = bmpHeight / scale;

    //把处理后的图像数据存到lcd虚拟内存
    for(int row = 0; row < scaleHeight; row++)
    {
        for(int column = 0; column < scaleWidth; column++)
        {
            lcdBuf[row + posY][column + posX] = tempBuf[(scaleHeight - row) * scale][column * scale];
        }
    }

	close(bmpFd);

	log_debug("show scaled %s completed",bmpFile);
}
