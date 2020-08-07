CC = gcc
CFLAGS = -g -Wall

TARGET = cat
.PHONY: all clean format check

all: $(TARGET)

clean:
	- rm -f *.o $(TARGET) test
format:
	clang-format -i *.c

check: all test
	./test

cat: cat.o
