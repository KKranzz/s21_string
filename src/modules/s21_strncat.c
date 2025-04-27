#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*ptr != '\0') {
    ptr++;
  }

  while (n-- && *src != '\0') {
    *ptr++ = *src++;
  }

  *ptr = '\0';

  return dest;
}