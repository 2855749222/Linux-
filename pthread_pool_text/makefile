CC := gcc
CFLAGS := -Wall -O2
TARGET := main
SRCS := main.c pthread_pool.c

all:  $(TARGET)
# 生成可执行文件s
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lpthread 
