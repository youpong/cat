CC = gcc
CFLAGS = -g -Wall

TARGET = cat
.PHONY: all clean format test

all: $(TARGET)

clean:
	- rm -f *.o $(TARGET)
format:
	clang-format -i *.c

test: all
	./test.sh

cat: cat.o
