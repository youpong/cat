#include <stdio.h>

int main(int argc, char **argv) {
  char **args = argv + 1;
  FILE *f;

  f = stdin;
  if (argc != 1) {
    f = fopen(*args, "r");
  }

  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }

  return 0;
}
