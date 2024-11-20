CC := arm-linux-gcc
CFLAGS := -Wall -O2
TARGET := main1
SRCS := main.c fun/show_mmap.c fun/load_bmp_as_argb.c fun/list.c fun/get_touch_index.c fun/show_font.c lib/libfont.a




all:  $(TARGET)
# 生成可执行文件s
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lpthread -lm
