#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; ++i) {
    if (s[i] == uc) {
      return (void *)(s + i);
    }
  }
  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
  }

  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // Приводим указатели к типу char для работы с байтами
  char *destination = (char *)dest;
  const char *source = (const char *)src;

  // Копируем каждый байт из source в destination
  for (s21_size_t i = 0; i < n; ++i) {
    destination[i] = source[i];
  }

  // Возвращаем указатель на начало destination
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; ++i) {
    s[i] = uc;
  }
  return str;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest == s21_NULL || src == s21_NULL) {
    return s21_NULL;  // Если переданы нулевые указатели, возвращаем нулевой
                      // указатель
  }

  char *original_dest =
      dest;  // Сохраняем указатель на начало строки назначения

  while (n > 0 && *src != '\0') {  // Пока не достигнут конец строки-источника
                                   // или не скопировано n символов
    *dest = *src;  // Копируем символ из строки-источника в строку-назначение
    dest++;  // Увеличиваем указатель на строку-назначение
    src++;  // Увеличиваем указатель на строку-источник
    n--;  // Уменьшаем счетчик скопированных символов
  }

  while (n > 0) {  // Если осталось еще место в строке-назначении
    *dest = '\0';  // Добавляем нулевой символ
    dest++;  // Увеличиваем указатель на строку-назначение
    n--;     // Уменьшаем счетчик
  }

  return original_dest;  // Возвращаем указатель на начало строки назначения
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    return 0;  // Если переданы нулевые указатели, возвращаем 0
  }

  const char *p;
  const char *s;
  s21_size_t count = 0;

  for (p = str1; *p != '\0'; p++) {  // Проходим по строке str1
    for (s = str2; *s != '\0'; s++) {  // Проходим по строке str2
      if (*p == *s) {
        return count;  // Если символ из str1 найден в str2, возвращаем текущее
                       // значение count
      }
    }
    count++;  // Увеличиваем count, так как текущий символ из str1 не найден в
              // str2
  }

  return count;  // Если не найдено совпадений, возвращаем длину строки str1
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  if (s21_strcspn(str1, str2) != s21_strlen(str1) && *str1 != '\0')
    res = (char *)str1 + s21_strcspn(str1, str2);
  return res;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str) {
    for (int i = 0; str[i]; i++) len++;
  }
  return len;
}

char *s21_strncat(char *str1, const char *str2, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(str1);
  s21_size_t i = 0;
  for (; i < n && str2[i]; i++) {
    str1[dest_len + i] = str2[i];
  }
  str1[dest_len + i] = '\0';
  return str1;
}

char *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;  // Проверка на нулевые указатели
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) {
    return s21_NULL;  // Проверка, что start_index не превышает длину строки src
  }

  // Выделение памяти для новой строки
  char *new_str = (char *)malloc((src_len + str_len + 1) * sizeof(char));
  if (new_str == s21_NULL) {
    return s21_NULL;  // Проверка на успешное выделение памяти
  }

  // Копирование src в новую строку до start_index
  s21_memcpy(new_str, src, start_index);

  // Копирование str в новую строку начиная с start_index
  s21_memcpy(new_str + start_index, str, str_len);

  // Копирование оставшейся части src в новую строку
  s21_memcpy(new_str + start_index + str_len, src + start_index,
             src_len - start_index);

  // Установка завершающего нулевого символа
  new_str[src_len + str_len] = '\0';

  return new_str;
}

char *s21_strdup(const char *src) {
  if (!src) return s21_NULL;
  s21_size_t len = s21_strlen(src);
  char *dst = malloc(len + 1);
  if (!dst) return s21_NULL;
  s21_strncpy(dst, src, len);
  dst[len] = '\0';
  return dst;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) i++;
  return c == str[i] ? (char *)str + i : s21_NULL;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) return s21_strdup("");

  s21_size_t src_len = s21_strlen(src);

  // Удаление начальных вхождений trim_chars
  s21_size_t start = 0;
  while (src[start] != '\0' && s21_strchr(trim_chars, src[start]) != s21_NULL) {
    start++;
  }

  // Удаление конечных вхождений trim_chars
  s21_size_t end = src_len;
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != s21_NULL) {
    end--;
  }

  // Копирование оставшейся части строки
  char *trimmed_str = s21_strdup(src + start);
  if (!trimmed_str) return s21_NULL;
  trimmed_str[end - start] = '\0';  // Установка завершающего нуля
  return trimmed_str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  while ((*str1 || *str2) && n--)
    if (*str1++ != *str2++) {
      res = (unsigned char)*--str1 - (unsigned char)*--str2;
      break;
    }
  return res;
}
int s21_atoi(const char *str) {
    int res = 0;
    int sign = 1;
    int overflow = 0;

    while (*str == ' ') str++;

    if (*str == '-') {
        str++;
        sign = -1;
    }

    if (*str == '+') {
        str++;
    }

    while (*str && *str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        if (res < 0) {
            overflow = 1;
            break;
        }
        str++;
    }
    if (overflow)
        res = sign > 0 ? INT32_MAX : INT32_MIN;
    else
        res *= sign;

    return res;
}

char *s21_strcpy(char *dest, const char *src) {
    for (int i = 0; src[i]; i++) {
        dest[i] = src[i];
    }

    dest[s21_strlen(src)] = '\0';

    return dest;
}

char *s21_strcat(char *dest, const char *src) {
    int dest_len = s21_strlen(dest);
    int i = 0;

    for (; src[i]; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *to = (char *)dest;
    char *from = (char *)src;

    char *tmp = (char *)malloc(sizeof(char) * n);

    if (tmp) {
        s21_memcpy(tmp, from, n);
        s21_memcpy(to, tmp, n);
        free(tmp);
    }
    return dest;
}

