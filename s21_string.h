#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUFF_SIZE 512

#define s21_size_t unsigned long long
#define s21_NULL (void *)0

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strerror(int errnum);

s21_size_t s21_strlen(const char *str);
char *s21_strncat(char *str1, const char *str2, s21_size_t n);
char *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_strdup(const char *src);
char *s21_strchr(const char *str, int c);
void *s21_trim(const char *src, const char *trim_chars);

s21_size_t s21_strlen(const char *str);
char *s21_strncat(char *str1, const char *str2, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcat(char *dest, const char *src);

char *s21_strcpy(char *dest, const char *src);

int s21_atoi(const char *str);
s21_size_t s21_strspn(const char *str1, const char *str2);

void *s21_memmove(void *dest, const void *src, s21_size_t n);

int s21_isdigit(char c);

#endif  // S21_STRING_H_