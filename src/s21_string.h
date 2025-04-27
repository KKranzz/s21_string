#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_types.h"

// STRING FUNC
void *s21_memchr(const void *str, int c, s21_size_t n);             // 1
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);   // 2
void *s21_memcpy(void *dest, const void *src, s21_size_t n);        // 3
void *s21_memset(void *str, int c, s21_size_t n);                   // 4
char *s21_strncat(char *dest, const char *src, s21_size_t n);       // 5
char *s21_strchr(const char *str, int c);                           // 6
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);  // 7
char *s21_strncpy(char *dest, const char *src, s21_size_t n);       // 8
s21_size_t s21_strcspn(const char *str1, const char *str2);         // 9
char *s21_strerror(int errnum);                                     // 10
s21_size_t s21_strlen(const char *str);                             // 11
char *s21_strpbrk(const char *str1, const char *str2);              // 12
char *s21_strrchr(const char *str, int c);                          // 13
char *s21_strstr(const char *haystack, const char *needle);         // 14
char *s21_strtok(char *str, const char *delim);                     // 15
// sad
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
// end sad

// sprintf
int s21_sprintf(char *str, const char *format, ...);

#endif
