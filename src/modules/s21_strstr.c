#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    for (; *haystack != '\0' && result == NULL; haystack++) {
      const char *h = haystack;
      const char *n = needle;

      while (*h != '\0' && *n != '\0' && *h == *n) {
        h++;
        n++;
      }

      if (*n == '\0') {
        result = (char *)haystack;
      }
    }
  }

  return result;
}