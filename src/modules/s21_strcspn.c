#include "../s21_string.h"
#include "../s21_types.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s1 = str1;

  s21_size_t len = 0;
  int found = 0;

  while (*s1 != '\0' && !found) {
    const char *s2 = str2;
    while (*s2 != '\0' && !found) {
      if (*s1 == *s2) {
        found = 1;
      }
      s2++;
    }
    if (!found) {
      len++;
      s1++;
    }
  }

  return len;
}