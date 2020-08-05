#include <stdio.h>

int main(int argc, char **argv) {
  char **args = argv + 1;

  if (argc == 1) {
    int c;
    while ((c = getchar()) != EOF) {
      putchar(c);
    }

    return 0;
  }

  FILE *f;
  f = fopen(*args, "r");

  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }

  return 0;
}
