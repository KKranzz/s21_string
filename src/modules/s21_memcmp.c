#include "../s21_string.h"

int s21_memcmp(const void *memptr1, const void *memptr2, s21_size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)memptr1;
  const unsigned char *ptr2 = (const unsigned char *)memptr2;
  s21_size_t i = 0;
  int res = 0;

  while (i < n && res == 0) {
    res = ptr1[i] - ptr2[i];
    i++;
  }

  return res;
}
