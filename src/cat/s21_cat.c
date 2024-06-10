#include "s21_cat.h"

int main(int argc, char **argv) {
  s21_cat_programm(argc, argv);
  return 0;
}

void s21_cat_programm(int argc, char **argv) {
  if (argc > 1) {
    options config = {0};
    if (scanOptions(argc, argv, &config)) {
      for (int x = (argc - config.numberFiles); x < argc; x += 1) {
        FILE *file = fopen(argv[x], "r");
        if (file != NULL) {
          printData(file, &config);
          fclose(file);
        } else {
          fprintf(stderr, ERROR_01, argv[x]);
        }
      }
    }
  }
}

int scanOptions(int argc, char **argv, options *config) {
  int indexStartFiles = 1, status = 1, x = 1;

  for (; (x < argc && argv[x][0] == '-'); indexStartFiles = (x += 1)) {
    if (!strcmp(argv[x], "-b") || !strcmp(argv[x], "--number-nonblank")) {
      config->b = (config->n = 0) + 1;
    } else if (!strcmp(argv[x], "-s") || !strcmp(argv[x], "--squeeze-blank")) {
      config->s = 1;
    } else if (!strcmp(argv[x], "-n") || !strcmp(argv[x], "--number")) {
      config->n = config->b ? 0 : 1;
    } else if (!strcmp(argv[x], "-T")) {
      config->t = 1;
    } else if (!strcmp(argv[x], "-v")) {
      config->v = 1;
    } else if (!strcmp(argv[x], "-t")) {
      config->t = 1;
      config->v = 1;
    } else if (!strcmp(argv[x], "-e")) {
      config->e = 1;
      config->v = 1;
    } else if (!strcmp(argv[x], "-E")) {
      config->e = 1;
    } else {
      fprintf(stderr, ERROR_02, argv[x][1]);
      status = 0;
    }
  }

  config->numberFiles = argc - indexStartFiles;

  return status;
}

void printData(FILE *file, options *config) {
  int counterS = 0;   // Counter for consecutive empty lines
  int counterB = 0;   // Counter for non-blank lines
  int newLine = 0;    // Flag for tracking a new line after a number
  int emptyLine = 0;  // Flag for tracking an empty line

  for (char sym = '0'; (sym = getc(file)) != EOF;) {
    if (config->s && counterS == 0 && sym == '\n') {
      counterS += 1;
    } else if (counterS != 0 && sym == '\n') {
      counterS += 1;
      emptyLine = 1;
    } else if (counterS > 1 && sym != '\n') {
      counterS = 0;
      config->e ? printf("$\n") : printf("\n");
      if (config->n != 0) printf("%6d\t", config->n++);
    } else {
      counterS = 0;
    }

    if (config->n != 0 || config->b != 0) {
      if (newLine == 1 && !(newLine = 0)) {
        printf("%6d\t", config->n++);
      }
      if (config->n == 1) {
        printf("%6d\t", config->n++);
      }
      if (config->b == 1) {
        printf("%6d\t", config->b++);
      }

      if (sym == '\n' && config->n != 0 && emptyLine == 0) {
        newLine = 1;
      }
      if (sym == '\n' && config->b != 0) {
        counterB += 1;
      }
      if (sym != '\n' && counterB != 0 && counterS == 0) {
        if (!(counterB = 0)) {
          printf("%6d\t", config->b++);
        }
      }
    }

    if (sym == '\n' && config->e && emptyLine == 0) {
      printf("$");
    }

    if (config->v) {
      if (sym < 32 && sym != 9 && sym != 10) {
        if (sym += 64) {
          printf("^");
        }
      }
      if (sym == 127) {
        if ((sym = '?')) {
          printf("^");
        }
      }
    }

    if (config->t && sym == '\t') {
      if ((sym = 'I')) {
        printf("^");
      }
    }

    if (emptyLine == 0) {
      printf("%c", sym);
    }

    emptyLine = 0;
  }
}
