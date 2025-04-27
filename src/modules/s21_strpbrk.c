#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *s1 = str1;

  char *res = S21_NULL;
  int found = 0;
  while (*s1 != '\0' && !found) {
    const char *s2 = str2;
    while (*s2 != '\0' && !found) {
      if (*s1 == *s2) {
        res = (char *)s1;
        found = 1;
      }
      s2++;
    }
    s1++;
  }

  return res;
}