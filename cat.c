#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *progname;

static void cat(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }
}

static bool is_dir(char *path) {
  bool ret = false;

  DIR *dir = opendir(path);
  if (dir != NULL) {
    closedir(dir);
    ret = true;
  }

  return ret;
}

/** returns NULL if failure */
static FILE *open_file(char *path) {
  static bool used_stdin = false;

  if (strcmp(path, "-") == 0) {
    if (used_stdin) {
      fprintf(stderr, "%s: multiple - is specified\n", progname);
      return NULL;
    }
    used_stdin = true;
    return stdin;
  }

  if (is_dir(path)) {
    fprintf(stderr, "%s: %s: is directory\n", progname, path);
    return NULL;
  }

  FILE *f = fopen(path, "r");
  if (f == NULL) {
    fprintf(stderr, "%s: %s: %s\n", progname, path, strerror(errno));
    return NULL;
  }

  return f;
}

int main(int argc, char **argv) {
  progname = *argv++;

  if (argc == 1) {
    cat(stdin);
    return EXIT_SUCCESS;
  }

  int ret = EXIT_SUCCESS;
  for (char **p = argv; *p != NULL; ++p) {
    FILE *f = open_file(*p);
    if (f == NULL) {
      ret = EXIT_FAILURE;
      continue;
    }
    cat(f);
    fclose(f);
  }

  return ret;
}
