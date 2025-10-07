#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e_flag;  //Шаблон.
  int i_flag;  //Игнорирует различия регистра.
  int v_flag;  //Инвертирует смысл поиска соответствий.
  int c_flag;  //Выводит только количество совпадающих строк.
  int l_flag;  //Выводит только совпадающие файлы.
  int n_flag;  //Предваряет каждую строку вывода номером строки из файла ввода.
  int h_flag;  //Выводит совпадающие строки, не предваряя их именами файлов.
  int s_flag;  //Подавляет сообщения об ошибках о несуществующих или нечитаемых
               //файлах
  int f_flag;  //Получает регулярные выражения из файла.
  int o_flag;  //Печатает только совпадающие (непустые) части совпавшей строки
  char *searc_string;
} Options;

char *get_string_from_file(FILE *file, int *end);
Options print_line(char *line, Options flags, int line_count, char *file_name);
void to_lowercase(char *str);
Options f_grep(char *file_name, Options flags);
Options f_grep_with_f(char *file_name, Options flags, FILE *patterns);