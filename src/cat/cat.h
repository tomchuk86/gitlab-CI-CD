#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b_flag;
  int e_flag;
  int n_flag;
  int s_flag;
  int t_flag;
} Options;

char *get_string_from_file(FILE *file, int *end);
void print_line(char *line, Options flags, int num_lines, int *end);
void f_cat(char *file_name, Options flags);
