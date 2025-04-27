#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *returnvalue = S21_NULL;
  int flag = 0;
  char ch = (char)c;

  while (*str != '\0' && !flag) {
    if (*str == ch) {
      returnvalue = (char *)str;
      flag = 1;
    }
    str++;
  }

  if (!flag && ch == '\0') {
    returnvalue = (char *)str;
  }

  return returnvalue;
}