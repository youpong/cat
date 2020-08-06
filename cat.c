#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>

static void cat(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }
}

static bool is_dir(char *path) {
  return opendir(path) ? true : false;
}

int main(int argc, char **argv) {
  char **args = argv + 1;
  int ret = EXIT_SUCCESS;

  if (argc == 1) {
    cat(stdin);
    return 0;
  }

  for (char **p = args; *p != NULL; p++) {
    if (is_dir(*p)) {
      fprintf(stderr, "%s: %s: is directory\n", argv[0], *p);
      ret = EXIT_FAILURE;
      continue;
    }
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
