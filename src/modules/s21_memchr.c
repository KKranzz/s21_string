#include "../s21_string.h"
#include "../s21_types.h"

void *s21_memchr(const void *s, int c, s21_size_t n) {
  void *returnvalue = S21_NULL;
  int flag = 0;

  const unsigned char *str = (const unsigned char *)s;
  unsigned char uc = (unsigned char)c;

  for (s21_size_t i = 0; i < n && !flag; i++) {
    if (str[i] == uc) {
      returnvalue = (void *)&str[i];
      flag = 1;
    }
  }
  return returnvalue;
}
