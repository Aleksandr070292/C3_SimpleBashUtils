#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_01 "s21_cat: %s: No such file or directory\n"
#define ERROR_02 "s21_cat: invalid option -- '%c'\n"

typedef struct {
  int b;            // Number nonblank lines
  int e;            // End of line
  int n;            // Number lines
  int s;            // Squeeze blank lines
  int t;            // Show tabs
  int v;            // Show non-printing characters
  int numberFiles;  // Number of files to process
} options;

// Function prototypes
void s21_cat_programm(int argc, char **argv);
int scanOptions(int argc, char **argv, options *config);
void printData(FILE *file, options *config);

#endif  // SRC_CAT_S21_CAT_H_