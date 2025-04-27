#include "../s21_string.h"
#include "../s21_types.h"

int is_delim(char c, const char *delim) {
  while (*delim != '\0') {
    if (c == *delim) return 1;
    delim++;
  }
  return 0;
}

char *s21_strtok(char *str, const char *delim) {
  static char *p;
  if (!str) str = p;
  char *returnvalue;
  int flag = 0;
  if (!str) return NULL;
  while (flag == 0) {
    if (is_delim(*str, delim))
      str++;
    else if (*str == '\0')
      return NULL;
    else
      flag = 1;
  }
  char *ret = str;
  flag = 0;
  while (flag == 0) {
    if (*str == '\0') {
      p = str;
      returnvalue = ret;
      flag = 1;
    }
    if (is_delim(*str, delim)) {
      *str = '\0';
      p = str + 1;
      returnvalue = ret;
      flag = 1;
    }
    str++;
  }
  return returnvalue;
}