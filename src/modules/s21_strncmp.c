#include "../s21_string.h"

int s21_strncmp(const char *s1, const char *s2, s21_size_t n) {
  s21_size_t i = 0;
  int res = 0;
  while (i != n && res == 0 && (s1[i] != '\0' || s2[i] != '\0')) {
    res = s1[i] - s2[i];
    i++;
  }
  return res;
}