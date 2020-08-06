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
  bool ret;

  DIR *dir = opendir(path);
  ret = dir != NULL ? true : false;
  closedir(dir);

  return ret;
}

/** NULL if failure */
static FILE *open_file(char *path) {
  if (strcmp(path, "-") == 0) {
    return fdopen(0, "r");
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

/** 
 * close FILE except stdin 
 * support ./cat - -
*/
static void close_file(char *path, FILE *file) {
  if (strcmp(path, "-") != 0) {
    fclose(file);
  }
}

int main(int argc, char **argv) {
  char **args = argv + 1;
  int ret = EXIT_SUCCESS;

  progname = argv[0];

  if (argc == 1) {
    cat(stdin);
    return 0;
  }

  for (char **p = args; *p != NULL; p++) {
    FILE *f = open_file(*p);
    if (f == NULL) {
      ret = EXIT_FAILURE;
      continue;
    }
    cat(f);
    close_file(*p, f);
  }

  return ret;
}
