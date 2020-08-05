CC = gcc
CFLAGS = -g -Wall

TARGET = cat
.PHONY: all clean format check

all: $(TARGET)

clean:
	- rm -f *.o $(TARGET)
format:
	clang-format -i *.c

check: all
	./test.sh

cat: cat.o
