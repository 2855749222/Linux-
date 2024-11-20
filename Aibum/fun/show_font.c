#include "../include/font.h"

// // lcd设备结构体
// struct LcdDevice
// {
// 	int fd;
// 	unsigned int *mp; // 保存映射首地址
// };


//1.初始化字库 
// font *fontLoad(char *fontPath);

// //2.设置字体的大小 
// void fontSetSize(font *f, s32 pixels);

// //3.设置字体输出框的大小
// bitmap *createBitmap(u32 width, u32 height, u32 byteperpixel);

// //可以指定输出框的颜色
// bitmap *createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);


// //4.把字体输出到输出框中
// void fontPrint(font *f, bitmap *screen, s32 x, s32 y, char *text, color c, s32 maxWidth);

// //5.把输出框的所有信息显示到LCD屏幕中 
// void show_font_to_lcd(unsigned int *p,int px,int py,bitmap *bm);

// // 关闭字体库
// void fontUnload(font *f);

// // 关闭bitmap
// void destroyBitmap(bitmap *bm);
struct LcdDevice *init_lcd(const char *device)
{
	// 申请空间
	struct LcdDevice *lcd = malloc(sizeof(struct LcdDevice));
	if (lcd == NULL)
	{
		return NULL;
	}

	// 1打开设备
	lcd->fd = open(device, O_RDWR);
	if (lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return NULL;
	}

	// 映射
	lcd->mp = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);

	return lcd;
}
struct LcdDevice *lcd = NULL;
font *f = NULL;
bitmap *bm = NULL;
int bit(char *buf, int x, int y)
{
	// 初始化Lcd
	struct LcdDevice *lcd = init_lcd("/dev/fb0");

	// 打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f, 15);

	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(55, 30, 4, getColor(0, 200, 225, 220));

	fontPrint(f, bm, 5, 3, buf, getColor(0, 0, 0, 0), 50);
	show_font_to_lcd(lcd->mp, x, y, bm);

	// 关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	close(lcd->fd);
	munmap(lcd->mp, 800 * 480 * 4);
	free(lcd);

	return 0;
}


int show_pan_size(int size)
{
	printf("size = %d\n",size);
	char buf [3]={0};
	int i = 0;
	if (size >= 10)
	{
		buf[0] = size / 10 + '0';
		buf[1] = size % 10 + '0';
		buf[2] = '\0';
	}
	else
	{
		buf[0] = size % 10 + '0';
		buf[1] = '\0';
	}
	
	// 初始化Lcd
	printf("buf = %s\n",buf);

	struct LcdDevice *lcd = init_lcd("/dev/fb0");

	// 打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f, 35);

	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(55, 30, 4, getColor(0, 201, 174, 255));

	fontPrint(f, bm, 9, 0, buf, getColor(0, 0, 0, 0), 50);
	show_font_to_lcd(lcd->mp, 600, 8, bm);

	// 关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	close(lcd->fd);
	munmap(lcd->mp, 800 * 480 * 4);
	free(lcd);

	return 0;
}
void show_borad_font(char *buf)
{
	
	// 初始化Lcd
	printf("buf = %s\n",buf);

	struct LcdDevice *lcd = init_lcd("/dev/fb0");

	// 打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f, 25);

	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(150, 30, 4, getColor(0, 255, 255, 255));

	fontPrint(f, bm, 9, 0, buf, getColor(0, 0, 0, 0), 150);
	show_font_to_lcd(lcd->mp, 0, 55, bm);

	// 关闭字体，关闭画板
	sleep(1);
	fontUnload(f);
	destroyBitmap(bm);
	close(lcd->fd);
	munmap(lcd->mp, 800 * 480 * 4);
	free(lcd);

	return 0;
}
// int show_font()
// {
    

// 	// 初始化Lcd
// 	struct LcdDevice *lcd = init_lcd("/dev/fb0");

// 	// 打开字体
// 	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

// 	// 字体大小的设置
// 	fontSetSize(f, 40);

// 	// 创建一个画板（点阵图）
// 	bitmap *bm = createBitmapWithInit(150, 150, 4, getColor(0, 255, 0, 255)); // 也可使用createBitmap函数，改变画板颜色
// 	// getColor(0, 255, 0, 0)  ABGR
// 	// bitmap *bm = createBitmap(288, 100, 4);

// 	char buf[] = "玩家1下子:";

// 	// 将字体写到点阵图上
// 	fontPrint(f, bm, 0, 0, buf, getColor(0, 0, 0, 0), 200);

// 	// 把字体框输出到LCD屏幕上
// 	show_font_to_lcd(lcd->mp, 0, 0, bm);

// 	// 关闭字体，关闭画板
// 	fontUnload(f);
// 	destroyBitmap(bm);

// 	// font *f = fontLoad("/usr/share/fonts/simfang.ttf");
// 	// // 字体大小的设置
// 	// fontSetSize(f, 100);

// 	// // 创建一个画板（点阵图）
// 	// bitmap *bm = createBitmapWithInit(200, 400, 4, getColor(0, 0, 0, 255)); // 也可使用createBitmap函数，改变画板颜色
// 	// // getColor(0, 255, 0, 0)  ABGR
// 	// // bitmap *bm = createBitmap(288, 100, 4);

// 	// char buf[] = "Hello你好";

// 	// // 将字体写到点阵图上
// 	// fontPrint(f, bm, 0, 0, buf, getColor(0, 255, 255, 255), 200);

// 	// // 把字体框输出到LCD屏幕上
// 	// show_font_to_lcd(lcd->mp, 0, 0, bm);
//     return 0;
// }
