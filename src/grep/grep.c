#include "grep.h"

int main(int argc, char *argv[]) {
  Options flags;
  flags.c_flag = 0, flags.e_flag = 0, flags.i_flag = 0, flags.v_flag = 0,
  flags.l_flag = 0, flags.n_flag = 0;
  flags.h_flag = 0, flags.s_flag = 0, flags.f_flag = 0, flags.o_flag = 0;
  flags.searc_string = NULL;
  char **file_names = malloc(sizeof(char *));
  int files_counter = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j]; j++) {
        switch (argv[i][j]) {
          case 'c':
            flags.c_flag = 1;
            break;
          case 'n':
            flags.n_flag = 1;
            break;
          case 'e':
            flags.e_flag = 1;
            break;
          case 'i':
            flags.i_flag = 1;
            break;
          case 'v':
            flags.v_flag = 1;
            break;
          case 'l':
            flags.l_flag = 1;
            break;
          case 'h':
            flags.h_flag = 1;
            break;
          case 's':
            flags.s_flag = 1;
            break;
          case 'f':
            flags.f_flag = 1;
            break;
          case 'o':
            flags.o_flag = 1;
            break;
          default:
            printf("Invalid option: -%c\n", argv[i][j]);
            return 1;
        }
      }
    } else {
      if (flags.searc_string == NULL) {
        flags.searc_string = argv[i];
      } else {
        file_names[files_counter] = argv[i];
        files_counter++;
        file_names = realloc(file_names, sizeof(char *) * (files_counter + 1));
      }
    }
  }
  if (files_counter == 1) flags.h_flag = 1;
  if (flags.f_flag == 1) {
    flags.e_flag = 1;
    char *pat = flags.searc_string;
    FILE *patterns = fopen(pat, "r");
    if (!patterns) {
      printf("Cannot open file %s", flags.searc_string);
    }

    for (int i = 0; i < files_counter; i++) {
      FILE *patterns = fopen(pat, "r");
      flags = f_grep_with_f(file_names[i], flags, patterns);
    }
    fclose(patterns);
  } else {
    for (int i = 0; i < files_counter; i++) {
      flags = f_grep(file_names[i], flags);
    }
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
Options print_line(char *line, Options flags, int line_count, char *file_name) {
  char *line_for_cmp = malloc((strlen(line) + 2) * sizeof(char));
  line_for_cmp = strcpy(line_for_cmp, line);
  if (flags.i_flag) {
    to_lowercase(line_for_cmp);
    to_lowercase(flags.searc_string);
  }
  int ret = 1;
  regex_t reg;
  if (flags.e_flag) {
    ret = regcomp(&reg, flags.searc_string, REG_EXTENDED);
    ret = regexec(&reg, line, 0, NULL, 0);
  }
  if (flags.v_flag ^
      (ret == 0 || (strstr(line_for_cmp, flags.searc_string) != NULL))) {
    if (flags.l_flag || flags.c_flag) {
      if (flags.l_flag > 0) {
        flags.l_flag++;
      }
      if (flags.c_flag > 0) flags.c_flag++;
    } else {
      if (flags.h_flag != 1) printf("%s:", file_name);
      if (flags.n_flag) {
        printf("%d:", line_count);
      }
      if (flags.o_flag) {
        printf("%s\n", flags.searc_string);
      } else {
        printf("%s\n", line);
      }
    }
  }
  free(line_for_cmp);
  if (flags.e_flag) regfree(&reg);
  return flags;
}
void to_lowercase(char *str) {
  if (str == NULL) {
    return;  // Проверка на NULL перед продолжением
  }

  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = tolower(
        (unsigned char)str[i]);  // Преобразование символа в нижний регистр
  }
}
Options f_grep(char *file_name, Options flags) {
  FILE *fp = fopen(file_name, "r");
  if (!fp) {
    if (flags.s_flag != 1) printf("Cannot open file %s\n", file_name);
    return flags;
  }

  char *line = NULL;
  int line_count = 0;
  int end = 1;
  if (flags.searc_string == NULL) end = 0;

  while (end && (line = get_string_from_file(fp, &end))) {
    line_count++;
    flags = print_line(line, flags, line_count, file_name);
    free(line);
    line = NULL;
  }

  if (flags.c_flag > 0) {
    if (flags.h_flag != 1) printf("%s:", file_name);
    printf("%d\n", flags.c_flag - 1);
    flags.c_flag = 1;  // Сброс флага
  }

  if (flags.l_flag > 1) {
    printf("%s\n", file_name);
    flags.l_flag = 1;  // Сброс или установка флага
  }
  free(line);  // Освобождаем память сразу после использования
  fclose(fp);
  return flags;
}

Options f_grep_with_f(char *file_name, Options flags, FILE *patterns) {
  char *pattern = NULL;
  int end = 1;
  while (end && (pattern = get_string_from_file(patterns, &end))) {
    if (strlen(pattern) > 0) {
      flags.searc_string = pattern;
      flags = f_grep(file_name, flags);
    }
    free(pattern);
    pattern = NULL;
  }
  free(pattern);
  return flags;
}