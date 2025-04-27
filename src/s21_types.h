#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifndef MYNULL
#define MYNULL
#define S21_NULL ((void *)0)
#endif

#ifndef MYSIZET
#define MYSIZET

#if defined(x86_64) || defined(__amd64__) || defined(__aarch64__)
typedef unsigned long s21_size_t;  //%lu
#define MAX_MYSIZET ULLONG_MAX     //%llu
#elif defined(__i386__) || defined(_WIN32)
typedef unsigned int s21_size_t;
#define MAX_MYSIZET UINT_MAX
#else
#error "Unknown architecture"
#endif

#endif