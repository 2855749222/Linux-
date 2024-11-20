CC := arm-linux-gcc
CFLAGS := -Wall -O2
TARGET := main1
TIC_TARGET := Tic_tac_toe
LOGIN_TARGET := login
WHITEBOARD_TARGET := whiteboard
PICTURE_TARGET := picture
SRCS := main.c fun/get_touch_index.c fun/load_bmp_as_argb.c fun/show_mmap.c fun/show_font.c lib/libfont.a fun/show_time.c
TIC_SRCS := Tic_tac_toe.c fun/get_touch_index.c fun/load_bmp_as_argb.c fun/show_mmap.c fun/show_font.c lib/libfont.a 
LOGIN_SRCS := login.c fun/get_touch_index.c fun/load_bmp_as_argb.c fun/show_mmap.c fun/show_font.c lib/libfont.a
WHITEBOARD_SRCS := whiteboard.c fun/get_touch_index.c fun/load_bmp_as_argb.c fun/show_mmap.c fun/show_font.c lib/libfont.a fun/show_drow.c fun/boardfun.c fun/list.c
PICTURE_SRCS := picture_save.c fun/get_touch_index.c fun/load_bmp_as_argb.c fun/show_mmap.c
# 默认目标
# $(TIC_TARGET) $(LOGIN_TARGET) $(TARGET) $(WHITEBOARD_TARGET)
all:   $(TIC_TARGET) $(TARGET)
# 生成可执行文件s
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm -lpthread -lrt

 
# 生成可执行文件
$(TIC_TARGET): $(TIC_SRCS)
	$(CC) $(CFLAGS) $(TIC_SRCS) -o $(TIC_TARGET) -lm -lrt

# # 生成可执行文件
$(LOGIN_TARGET): $(LOGIN_SRCS)
	$(CC) $(CFLAGS) $(LOGIN_SRCS) -o $(LOGIN_TARGET) -lm

# # 生成可执行文件
# $(WHITEBOARD_TARGET): $(WHITEBOARD_SRCS)
# 	$(CC) $(CFLAGS) $(WHITEBOARD_SRCS) -o $(WHITEBOARD_TARGET) -lm

# # # 生成可执行文件
# $(PICTURE_TARGET): $(PICTURE_SRCS)
# 	$(CC) $(CFLAGS) $(PICTURE_SRCS) -o $(PICTURE_TARGET) 

#清理构建生成的文件
clean:
	rm -f    $(PICTURE_TARGET)

