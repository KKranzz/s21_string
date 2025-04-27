#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *returnvalue = S21_NULL;
  char ch = (char)c;

  while (*str != '\0') {
    if (*str == ch) {
      returnvalue = (char *)str;
    }
    str++;
  }

  if (ch == '\0') {
    returnvalue = (char *)str;
  }

  return returnvalue;
}