#include "font.h"

// // lcd设备结构体
// struct LcdDevice
// {
// 	int fd;
// 	unsigned int *mp; // 保存映射首地址
// };

// 初始化Lcd

int main()
{

	// 初始化Lcd
	struct LcdDevice *lcd = init_lcd("/dev/fb0");

	// 打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f, 40);

	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(150, 150, 4, getColor(0, 255, 0, 255)); // 也可使用createBitmap函数，改变画板颜色
	// getColor(0, 255, 0, 0)  ABGR
	// bitmap *bm = createBitmap(288, 100, 4);

	char buf[30] = "玩家1下子:";

	// 将字体写到点阵图上
	fontPrint(f, bm, 0, 0, buf, getColor(0, 0, 0, 0), 200);
	
	// 把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd->mp, 0, 0, bm);
	fontUnload(f);
	destroyBitmap(bm);	
	sleep(3);

	font *f1 = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f1, 40);

	// 创建一个画板（点阵图）
	bitmap *bm1 = createBitmapWithInit(150, 150, 4, getColor(0, 0, 11, 255)); // 也可使用createBitmap函数，改变画板颜色
	char buf1[30] = "玩家2下子:";

	// 将字体写到点阵图上
	fontPrint(f1, bm1, 0, 0, buf1, getColor(0, 0, 0, 0), 200);

	// 把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd->mp, 0, 0, bm1);

	// 关闭字体，关闭画板
	fontUnload(f1);
	destroyBitmap(bm);

	// font *f = fontLoad("/usr/share/fonts/simfang.ttf");
	// // 字体大小的设置
	// fontSetSize(f, 100);

	// // 创建一个画板（点阵图）
	// bitmap *bm = createBitmapWithInit(200, 400, 4, getColor(0, 0, 0, 255)); // 也可使用createBitmap函数，改变画板颜色
	// // getColor(0, 255, 0, 0)  ABGR
	// // bitmap *bm = createBitmap(288, 100, 4);

	// char buf[] = "Hello你好";

	// // 将字体写到点阵图上
	// fontPrint(f, bm, 0, 0, buf, getColor(0, 255, 255, 255), 200);

	// // 把字体框输出到LCD屏幕上
	// show_font_to_lcd(lcd->mp, 0, 0, bm);
}
