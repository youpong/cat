# for GNU Make
CFLAGS = -g -Wall -std=c17
ifneq (, $(strip $(findstring clang, $(CC))))
	LDFLAGS = -fuse-ld=mold
else
	LDFLAGS = -B/usr/local/libexec/mold
endif

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
	$(CC) -o $@ $(LIBS) $(LDFLAGS) $(OBJS)
