#CC = gcc

#CFLAGS = -g -Wall -std=c18 -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE
CFLAGS = -g -Wall -std=c18

LIBS =

TARGET = cat
SRCS = cat.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean format check tags

all: $(TARGET)

clean:
	- rm -f $(OBJS) $(TARGET) TAGS test

format:
	clang-format -i *.c

tags:
	etags $(SRCS) 

check: all test
	./test

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)
