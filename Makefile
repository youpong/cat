# for GNU Make

TARGET = cat
SRCS = cat.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -std=c18 -g -Wall -Wextra -pedantic
ifneq (, $(strip $(findstring clang, $(CC))))
	LDFLAGS = -fuse-ld=mold
else
	LDFLAGS = -B/usr/local/libexec/mold
endif

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
	$(CC) -o $@ $(LIBS) $(LDFLAGS) $(OBJS)
