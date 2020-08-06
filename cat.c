#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void cat(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }
}

int main(int argc, char **argv) {
  char **args = argv + 1;
  int ret = EXIT_SUCCESS;

  if (argc == 1) {
    cat(stdin);
    return 0;
  }

  for (char **p = args; *p != NULL; p++) {
    FILE *f = fopen(*p, "r");
    if (f == NULL) {
      fprintf(stderr, "%s: %s: %s\n", argv[0], *p, strerror(errno));
      ret = EXIT_FAILURE;
      continue;
    }
    cat(f);
    fclose(f);
  }

  return ret;
}
