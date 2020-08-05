#include <stdio.h>

static void cat(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }
}

int main(int argc, char **argv) {
  char **args = argv + 1;

  if (argc == 1) {
    cat(stdin);
    return 0;
  }

  for (char **p = args; *p != NULL; p++) {
    FILE *f = fopen(*args, "r");
    cat(f);
    fclose(f);
  }

  return 0;
}
