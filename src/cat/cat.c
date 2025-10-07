#include "cat.h"  // Убедитесь, что структура Options определена в этом файле

int main(int argc, char *argv[]) {
  Options flags;
  flags.b_flag = 0;
  flags.e_flag = 0;
  flags.n_flag = 0;
  flags.s_flag = 0;
  flags.t_flag = 0;

  char **file_names = NULL;
  int files_counter = 0;

  // Разбор аргументов
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j]; j++) {
        switch (argv[i][j]) {
          case 'b':
            flags.b_flag = 1;
            break;
          case 'n':
            flags.n_flag = 1;
            break;
          case 'e':
            flags.e_flag = 1;
            flags.t_flag = 1;
            break;
          case 's':
            flags.s_flag = 1;
            break;
          case 'E':
            flags.s_flag = 1;
            break;
          case 'v':
            flags.e_flag = 1;
            flags.t_flag = 1;
            break;
          case 't':
            flags.t_flag = 1;
            break;
          default:
            fprintf(stderr, "Invalid option: -%c\n", argv[i][j]);
            return 1;
        }
      }
    } else {
      char **temp = realloc(file_names, sizeof(char *) * (files_counter + 1));
      if (temp == NULL) {
        perror("Error reallocating memory");
        free(file_names);  // Освобождаем ранее выделенную память
        return 1;  // Завершение из-за ошибки
      }
      file_names = temp;
      file_names[files_counter] = argv[i];  // Добавляем файл
      files_counter++;
    }
  }

  if (flags.b_flag) flags.n_flag = 0;

  for (int i = 0; i < files_counter; i++) {
    f_cat(file_names[i], flags);
  }

  free(file_names);
  return 0;
}

char *get_string_from_file(FILE *file, int *end) {
  int len = 0;
  int capacity = 1;
  char *s = (char *)malloc(sizeof(char));

  char c = fgetc(file);

  while (c != EOF && c != '\n') {
    s[len++] = c;

    if (len >= capacity) {
      capacity *= 2;
      char *temp = (char *)realloc(s, capacity * sizeof(char));
      if (temp == NULL) {
        free(s);
        *end = 0;  // Завершение из-за ошибки выделения памяти
        return NULL;
      }
      s = temp;
    }

    c = fgetc(file);
  }

  if (c == EOF) {
    *end = 0;
  }
  s[len] = '\0';

  return s;
}

void print_line(char *line, Options flags, int num_lines, int *end) {
  if (*end && (flags.n_flag || (flags.b_flag && strlen(line) > 0))) {
    printf("%6d\t", num_lines);
  }

  for (char *p = line; *p; p++) {
    if (flags.t_flag && *p == '\t') {
      printf("^I");
    } else {
      putchar(*p);
    }
  }
}

void f_cat(char *file_name, Options flags) {
  FILE *fp = fopen(file_name, "r");

  if (!fp) {
    perror("Cannot open file");
    return;
  }

  char *line = NULL;
  int line_count = 0;
  int end = 1;
  int blank_lines = 0;

  while (end && (line = get_string_from_file(fp, &end))) {
    if (flags.s_flag && strlen(line) == 0) {
      if (blank_lines == 0) {
        blank_lines = 1;
      } else {
        free(line);
        continue;
      }
    } else {
      blank_lines = 0;
    }
    line_count++;
    print_line(line, flags, line_count, &end);

    if (strlen(line) == 0 && flags.b_flag) line_count--;

    if (flags.e_flag) {
      if (end) {
        printf("$\n");
      }
    } else {
      if (end) putchar('\n');
    }
    free(line);
  }

  fclose(fp);
}