#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags f = {0};  // Инициализируем флаги
  va_list va;
  va_start(va, format);
  char *str_beginning = str;  // Сохраняем начальную позицию строки
  while (*format) {
    if (*format != '%') {
      *str++ =
          *format++;  // Прямое копирование символов, если нет форматирования
      continue;
    } else {
      format++;
      s21_memset(&f, 0,
                 sizeof(flags));  // Обнуляем флаги перед каждым новым форматом
    }

    format = parse_flags(format, &f);  // Получаем флаги формата
    format = parse_width(format, &f, va);  // Получаем ширину поля
    format = parse_precision(format, &f, va);  // Получаем точность
    format = parse_length(format, &f);         // Получаем длину

    f.specifier = *format;
    format++;

    char buff[BUFF_SIZE] = {'\0'};  // Буфер для хранения значения формата
    format_argument(f, buff, va);  // Обрабатываем значение формата
    for (int i = 0; buff[i]; i++, str++)
      *str = buff[i];  // Копируем обработанное значение в строку

    if (f.specifier == 'n') {
      int *ret = va_arg(va, int *);
      if (ret) {
        *ret = str - str_beginning;  // Записываем количество символов,
                                     // записанных до этого момента
      }
    }
  }

  *str = '\0';  // Завершаем строку
  va_end(va);  // Завершаем работу с переменными аргументами
  return str - str_beginning;  // Возвращаем количество записанных символов
}

/*
   Эта функция разбирает флаги в строке формата и устанавливает соответствующие флаги в структуре flags.

   Параметры:
     - format: указатель на строку формата
     - f: указатель на структуру flags для хранения разобранных флагов

   Возвращаемое значение:
     - Обновленный указатель на строку формата после разбора флагов
*/
const char *parse_flags(const char *format, flags *f) {
  // Цикл по строке формата, пока не встретятся символы, не являющиеся флагами
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' || *format == '#') {
    // Проверяем текущий символ на каждый возможный флаг
    switch (*format) {
      case '0':
        // Если найден флаг '0', устанавливаем флаг zero в структуре flags
        f->zero = true;
        break;
      case '-':
        // Если найден флаг '-', устанавливаем флаг minus в структуре flags
        f->minus = true;
        break;
      case '+':
        // Если найден флаг '+', устанавливаем флаг plus в структуре flags
        f->plus = true;
        break;
      case ' ':
        // Если найден флаг ' ', устанавливаем флаг space в структуре flags
        f->space = true;
        break;
      case '#':
        // Если найден флаг '#', устанавливаем флаг hash в структуре flags
        f->hash = true;
        break;
    }
    // Переходим к следующему символу в строке формата
    format++;
  }
  // Возвращаем обновленный указатель на строку формата после разбора флагов
  return format;
}

/*
   Эта функция разбирает ширину поля в строке формата и устанавливает соответствующее значение в структуре flags.

   Параметры:
     - format: указатель на строку формата
     - f: указатель на структуру flags для хранения ширины поля
     - va: аргументы переменной длины для извлечения ширины поля, если она задана через '*'

   Возвращаемое значение:
     - Обновленный указатель на строку формата после разбора ширины поля
*/
const char *parse_width(const char *format, flags *f, va_list va) {
  if (*format == '*') {
    // Если ширина поля задана через '*', извлекаем значение из аргументов переменной длины
    format++;
    f->width = va_arg(va, int);
  } else if (s21_isdigit(*format)) {
    // Если ширина поля задана как число
    char tmp[BUFF_SIZE] = {'\0'};
    // Читаем число до достижения символа, не являющегося цифрой
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    // Преобразуем строку в число и сохраняем его как ширину поля
    f->width = s21_atoi(tmp);
  }
  // Возвращаем обновленный указатель на строку формата после разбора ширины поля
  return format;
}

/* 
   Эта функция разбирает точность в строке формата и устанавливает соответствующее значение в структуре flags. 
  
   Параметры:
     - format: указатель на строку формата
     - f: указатель на структуру flags для хранения точности
     - va: аргументы переменной длины для извлечения точности, если она задана через '*'

   Возвращаемое значение:
     - Обновленный указатель на строку формата после разбора точности 
 */
const char *parse_precision(const char *format, flags *f, va_list va) {
  // Если следующий символ - '.', устанавливаем флаг is_precision_set в true
  if (*format == '.') {
    f->is_precision_set = true;
    format++;
  }

  // Если следующий символ - '*', извлекаем значение точности из аргумента переменной длины
  if (*format == '*') {
    format++;
    f->precision = va_arg(va, int);
  } 
  // Если следующий символ - цифра, извлекаем значение точности из форматной строки
  else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->precision = s21_atoi(tmp);
  }
  
  return format;
}

/*
   Эта функция разбирает длину перед спецификатором формата и устанавливает соответствующее значение в структуре flags.
  
   Параметры:
     - format: указатель на строку формата
     - f: указатель на структуру flags для хранения длины
   
   Возвращаемое значение:
     - Обновленный указатель на строку формата после разбора длины

   Проверяем наличие длины перед спецификатором формата
*/

const char *parse_length(const char *format, flags *f) {
  
  switch (*format) {
    case 'h':
      // Если следующий символ - 'h', устанавливаем длину в 'h' и переходим к следующему символу
      f->length = 'h';
      format++;
      break;
    case 'l':
      // Если следующий символ - 'l', устанавливаем длину в 'l' и переходим к следующему символу
      f->length = 'l';
      format++;
      break;
    case 'L':
      // Если следующий символ - 'L', устанавливаем длину в 'L' и переходим к следующему символу
      f->length = 'L';
      format++;
      break;
  }
  return format;
}


/* 
   Эта функция обрабатывает значение аргумента в соответствии с форматом и записывает его в буфер.
   
   Параметры:
     - f: структура flags с информацией о формате
     - buff: указатель на буфер, в который будет записано значение
     - va: аргументы переменной длины 
*/

void format_argument(flags f, char *buff, va_list va) {
  /* Для каждого спецификатора формата вызывается соответствующая функция разбора */
  if (f.specifier == 'd' || f.specifier == 'i')
    parse_integer(f, buff, va); // разбор целых чисел
  else if (f.specifier == 'u')
    parse_unsigned_with_flags(f, buff, va); // разбор беззнаковых целых чисел
  else if (f.specifier == 'o')
    parse_octal_with_flags(f, buff, va); // разбор восьмеричных чисел
  else if (f.specifier == 'x' || f.specifier == 'X')
    parse_hex_with_flags(f, buff, va); // разбор шестнадцатеричных чисел
  else if (f.specifier == '%')
    buff[0] = '%'; // специальный символ процента
  else if (f.specifier == 'c')
    parse_char_with_flags(f, buff, va); // разбор символов
  else if (f.specifier == 's')
    parse_string_to_buffer(f, buff, va); // разбор строк
  else if (f.specifier == 'p')
    parse_pointer(f, buff, va); // разбор указателей
  else if (f.specifier == 'f')
    parse_float(f, buff, va); // разбор чисел с плавающей точкой
  else if (f.specifier == 'e' || f.specifier == 'E')
    parse_mantiss(f, buff, va); // разбор экспоненциальной записи числа
  else if (f.specifier == 'g' || f.specifier == 'G')
    parse_float_g_G(f, buff, va); // разбор чисел в общем виде
  if (f.specifier == 'G' || f.specifier == 'E' || f.specifier == 'X')
    to_upper(buff); // преобразование в верхний регистр, если необходимо
}


/* 
   Эта функция выполняет разбор аргумента как целого числа и запись его в буфер.
   
   Параметры:
     - f: структура flags с информацией о формате
     - buff: указатель на буфер, в который будет записано значение
     - va: аргументы переменной длины 
*/

void parse_integer(flags f, char *buff, va_list va) {
  int64_t val = va_arg(va, int64_t); // Получение аргумента из списка аргументов

  /* Приведение значения к соответствующему типу в зависимости от указанной длины */
  switch (f.length) {
    case 0: // без модификатора длины
      val = (int32_t)val;
      break;
    case 'h': // модификатор длины "short"
      val = (int16_t)val;
      break;
  }

  integer_to_string(val, buff, 10); // Преобразование целого числа в строку
  apply_precision_format(buff, f); // Применение точности
  format_flags(buff, f); // Применение флагов форматирования
}


/* 
   Преобразует целое число в строку.
   
   Параметры:
     - val: целое число для преобразования
     - ret: указатель на строку, куда будет записан результат
     - base: основание системы счисления 
*/

void integer_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'}; // временный буфер для хранения числа в обратном порядке
  int idx = BUFF_SIZE - 2; // индекс для записи в буфер, начиная с конца

  bool neg = val < 0 ? 1 : 0; // флаг отрицательности числа
  val = neg ? -val : val; // приведение к положительному значению

  if (val == 0) tmp[idx] = '0'; // если число ноль, записываем '0' в буфер

  // Преобразование числа в строку в обратном порядке
  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % base]; // получение символа для текущей цифры
    val /= base; // уменьшение числа на основание системы счисления
  }

  // Копирование символов из временного буфера в результирующий с учетом знака
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) { // если число отрицательное и текущий символ первый, добавляем знак "-"
      ret[j++] = '-';
    }

    ret[j] = tmp[idx];
  }
}


/* 
   Функция форматирования точности числа.
   Принимает строку buff и флаги форматирования f.
   Если длина строки меньше заданной точности, добавляет нули перед числом.
   Если точность равна 0 и число нулевое, строка становится пустой.
*/
void apply_precision_format(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'}; // Временный буфер для форматирования точности

  int sign = 0; // Индикатор отрицательного числа
  int len = s21_strlen(buff); // Длина строки buff

  // Если число отрицательное, сохраняем знак и уменьшаем длину на 1
  if (buff[0] == '-') {
    tmp[0] = '-'; // Сохраняем знак "-"
    len--;
    sign = 1; // Устанавливаем индикатор отрицательного числа
  }

  // Если заданная точность больше длины числа, добавляем нули перед числом
  if (f.precision > len) {
    int index;
    for (index = sign; index < f.precision - len + sign; index++) tmp[index] = '0'; // Добавляем нули

    // Копируем символы из buff в tmp, начиная с позиции sign
    for (int i = sign; buff[i]; i++, index++) tmp[index] = buff[i];

    // Копируем отформатированную строку из tmp обратно в buff
    s21_strcpy(buff, tmp);
  }

  // Если задана точность, равная 0, и число нулевое, делаем строку buff пустой
  if (f.is_precision_set && f.precision == 0 &&
      is_integer_specifier(f.specifier) && buff[0] == '0')
    buff[0] = '\0';
}


/*
   Проверяет, является ли спецификатор целым числом.
   Принимает символ спецификатора.
   Возвращает true, если спецификатор является целым числом (d, i, o, u, x, X), иначе false.
*/
bool is_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'}; // Список спецификаторов целых чисел
  bool res = false; // Результат проверки, изначально false
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = true; // Если найден совпадающий спецификатор, устанавливаем результат в true
      break; // Прерываем цикл, так как спецификатор найден
    }
  }
  return res; // Возвращаем результат проверки
}


/*
   Форматирует флаги для строки.
   Принимает указатель на строку buff и структуру flags f.
   Если установлен флаг plus, добавляет знак + перед числом (если не отрицательное или спецификатор не 'u').
   Если установлен флаг space, добавляет пробел перед числом (если не отрицательное или спецификатор не 'u').
   Если установлен флаг width, добавляет пробелы или нули до заданной ширины.
   Если спецификатор 'f' и в строке нет десятичной точки, добавляет ее в конец строки.
*/
void format_flags(char *buff, flags f) {
  char tmp[BUFF_SIZE + 1] = {'\0'}; // Временный буфер
  // Проверяем флаг plus и спецификатор
  if (f.plus && f.specifier != 'u') {
    // Если plus установлен и число не отрицательное (и не спецификатор 'u')
    tmp[0] = buff[0] == '-' ? buff[0] : '+'; // Если число отрицательное, копируем знак, иначе копируем '+'
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff); // Копируем остальную часть числа
    s21_strcpy(buff, tmp); // Копируем обратно в основной буфер
  } else if (f.space && buff[0] != '-' && f.specifier != 'u') {
    // Если space установлен и число не отрицательное (и не спецификатор 'u')
    tmp[0] = ' '; // Добавляем пробел в начало числа
    s21_strcpy(tmp + 1, buff); // Копируем остальную часть числа
    s21_strcpy(buff, tmp); // Копируем обратно в основной буфер
  }
  // Проверяем ширину
  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff); // Вычисляем количество пробелов или нулей, которые нужно добавить
    if (!f.minus) {
      // Если флаг минус не установлен, добавляем пробелы или нули слева
      s21_memset(tmp, f.zero ? '0' : ' ', idx); // Заполняем временный буфер пробелами или нулями
      s21_strcpy(tmp + idx, buff); // Копируем число после добавленных символов
    } else {
      // Если флаг минус установлен, добавляем пробелы справа
      s21_strcpy(tmp, buff); // Копируем число в начало временного буфера
      s21_memset(tmp + s21_strlen(tmp), ' ', idx); // Добавляем пробелы в конец
    }
    s21_strcpy(buff, tmp); // Копируем обратно в основной буфер
  }
  // Проверяем наличие десятичной точки для спецификатора 'f'
  if (!s21_strchr(buff, '.') && f.specifier == 'f') {
    s21_strcat(buff, "."); // Если нет точки, добавляем ее в конец числа
  }
}

/*
   Преобразует беззнаковое целое число в строку.
   Принимает беззнаковое целое число val, указатель на строку ret и основание системы base.
   Записывает результат в строку ret.
*/
void unsigned_num_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'}; // Буфер для временного хранения числа
  int idx = BUFF_SIZE - 1; // Индекс для буфера

  if (val == 0) { // Если число равно нулю
    buf[idx] = '0'; // Записываем ноль в буфер
    idx--; // Уменьшаем индекс
  }

  // Преобразование числа в строку в указанной системе счисления
  for (; val && idx; --idx, val /= base)
    buf[idx] = "0123456789abcdef"[val % base];

  // Копирование результата в строку ret
  for (int j = 0; buf[idx + 1]; idx++, j++) 
    ret[j] = buf[idx + 1];
}


/* 
   Парсит беззнаковое целое число в соответствии с заданными флагами и форматирует его в строку.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - va: va_list, содержащий беззнаковое целое число
*/
void parse_unsigned_with_flags(flags f, char *buff, va_list va) {
  // Получаем беззнаковое целое число из va_list
  uint64_t val = va_arg(va, uint64_t);
  
  // Приводим значение в соответствие с указанным спецификатором длины
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;  // Приведение к uint16_t при спецификаторе 'h'
      break;
    case 'l':
      val = (uint64_t)val;  // Приведение к uint64_t при спецификаторе 'l'
      break;
    case 0:
      val = (uint32_t)val;  // Приведение к uint32_t, если спецификатор отсутствует
  }
  
  // Преобразуем беззнаковое целое число в строку
  unsigned_num_to_string(val, buff, 10);
  
  // Применяем форматирование точности, если указано
  apply_precision_format(buff, f);
  
  // Применяем дополнительные флаги форматирования
  format_flags(buff, f);
}

/* 
   Парсит восьмеричное целое число в соответствии с заданными флагами и форматирует его в строку.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - va: va_list, содержащий восьмеричное целое число
*/
void parse_octal_with_flags(flags f, char *buff, va_list va) {
  buff[0] = '0'; // Устанавливаем начальный символ '0' для обозначения восьмеричного числа
  // Преобразуем восьмеричное целое число в строку, начиная с позиции f.hash в буфере
  integer_to_string(va_arg(va, int64_t), buff + f.hash, 8);
  // Применяем форматирование точности, если указано
  apply_precision_format(buff, f);
  // Применяем дополнительные флаги форматирования
  format_flags(buff, f);
}


/* 
   Преобразует строку в верхний регистр.

   Параметры:
   - str: Указатель на строку для преобразования
*/
void to_upper(char *str) {
  // Проход по строке до её завершения
  while (*str) {
    // Если символ в нижнем регистре, то преобразуем его в верхний
    if (*str >= 'a' && *str <= 'z') 
      *str = *str - 'a' + 'A';
    // Переходим к следующему символу
    str++;
  }
}


/* 
   Функция: is_all_zeroes
   Проверяет, содержит ли строка только символы '0'.

   Параметры:
   - buff: Указатель на строку для проверки

   Возвращает:
   - true, если строка содержит только символы '0'
   - false, в противном случае
*/
bool is_all_zeroes(char *buff) {
  for (int i = 0; buff[i]; i++)
    if (buff[i] != '0') // Если символ отличается от '0', то возвращаем false
      return false;
  return true; // Если все символы '0', возвращаем true
}

/* 
   Функция: parse_hex_with_flags
   Парсит шестнадцатеричное целое число в соответствии с заданными флагами и форматирует его в строку.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - va: va_list, содержащий шестнадцатеричное целое число
*/
void parse_hex_with_flags(flags f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t); // Получаем шестнадцатеричное целое число из va_list
  
  // Приводим значение в соответствие с указанным спецификатором длины
  switch (f.length) {
    case 0:
      val = (uint32_t)val; // Приведение к uint32_t, если спецификатор отсутствует
      break;
    case 'h':
      val = (uint16_t)val; // Приведение к uint16_t при спецификаторе 'h'
      break;
    case 'l':
      val = (uint64_t)val; // Приведение к uint64_t при спецификаторе 'l'
      break;
  }
  
  // Преобразуем шестнадцатеричное целое число в строку
  unsigned_num_to_string(val, buff, 16);
  
  // Применяем форматирование точности, если указано
  apply_precision_format(buff, f);
  
  // Если установлен флаг хэша, добавляем префикс '0x' к строке
  if (f.hash) {
    prepend_ox(buff, f);
  }
  
  // Применяем дополнительные флаги форматирования
  format_flags(buff, f);
}


/* 
   Функция: prepend_ox
   Добавляет префикс "0x" к строке, если это необходимо.

   Параметры:
   - buff: Указатель на строку
   - f: Флаги, указывающие параметры форматирования
*/
void prepend_ox(char *buff, flags f) {
  // Проверяем, нужно ли добавлять префикс "0x"
  if (!is_all_zeroes(buff) || f.specifier == 'p') {
    s21_memmove(buff + 2, buff, s21_strlen(buff)); // Сдвигаем строку на два символа вправо
    buff[0] = '0'; // Первый символ - '0'
    buff[1] = 'x'; // Второй символ - 'x'
  }
}


/* 
   Функция: parse_char_with_flags
   Парсит символ в соответствии с заданными флагами и форматирует его в строку.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - va: va_list, содержащий символ

   Примечание:
   - Если установлен спецификатор 'l', символ представляется как широкий символ (wchar_t).
   - В противном случае, символ представляется как обычный символ (char).
*/
void parse_char_with_flags(flags f, char *buff, va_list va) {
  if (f.length == 'l') {
    // Если спецификатор 'l', представляем символ как широкий символ (wchar_t)
    wchar_t w_c = va_arg(va, wchar_t);
    format_wide_char(buff, w_c); // Форматируем широкий символ
  } else {
    // В противном случае, символ представляем как обычный символ (char)
    char c = va_arg(va, int);
    format_char_to_buffer(f, buff, c); // Форматируем обычный символ
  }
}

/* 
   Функция: format_wide_char
   Форматирует широкий символ (wchar_t) в строку.

   Параметры:
   - buff: Буфер для хранения отформатированной строки
   - w_c: Широкий символ (wchar_t)

   Примечание:
   - Использует функцию wcstombs для конвертации широкого символа в многобайтовую строку.
   - Очищает буфер перед форматированием.
   - Проверяет ошибки при конвертации.
*/
void format_wide_char(char *buff, wchar_t w_c) {
  // Очищаем буфер
  s21_memset(buff, '\0', BUFF_SIZE);

  // Количество символов, сконвертированных в строку
  s21_size_t len = wcstombs(buff, &w_c, BUFF_SIZE);

  // Проверяем на ошибку в wcstombs
  if (len == (s21_size_t)-1) {
    return;
  }
}

/* 
   Функция: format_char_to_buffer
   Форматирует символ в соответствии с заданными флагами и записывает его в буфер.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - c: Символ для форматирования

   Примечание:
   - Если установлен флаг минус и задана ширина, символ размещается слева, остальные символы заполняются пробелами.
   - Если ширина задана, но флаг минус не установлен, символ размещается справа, остальные символы заполняются пробелами.
   - Если ширина не задана, символ размещается в начале строки.
*/
void format_char_to_buffer(flags f, char *buff, char c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = ' ';
      if (i == f.width - 1) buff[i] = c;
    }
  } else if (f.width) {
    buff[0] = c;
    for (int i = 1; i < f.width; i++) buff[i] = ' ';
  } else {
    buff[0] = c;
  }
}

/* 
   Функция: parse_string_to_buffer
   Парсит строку в соответствии с заданными флагами и форматирует её в буфер.

   Параметры:
   - f: Флаги, указывающие параметры форматирования
   - buff: Буфер для хранения отформатированной строки
   - va: va_list, содержащий строку

   Примечание:
   - Если установлен спецификатор 'l', строка представляется как широкая строка (wchar_t*).
   - В противном случае, строка представляется как обычная строка (char*).
*/
void parse_string_to_buffer(flags f, char *buff, va_list va) {
  if (f.length == 'l') {
    // Если спецификатор 'l', строка представляется как широкая строка (wchar_t*)
    wchar_t *wstr = va_arg(va, wchar_t*);
    format_wide_string(f, buff, wstr); // Форматируем широкую строку
  } else {
    // В противном случае, строка представляется как обычная строка (char*)
    char *str = va_arg(va, char*);
    format_string(f, buff, str); // Форматируем обычную строку
  }
}


void format_string(flags f, char *buff, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void format_wide_string(flags f, char *buff, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void parse_pointer(flags f, char *buff, va_list va) {
  unsigned_num_to_string(va_arg(va, uint64_t), buff, 16);
  apply_precision_format(buff, f);
  prepend_ox(buff, f);
  format_flags(buff, f);
}

void parse_float(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!f.is_precision_set) {
    f.precision = 6;
  }

  double_to_string(val, buff, f);
  format_flags(buff, f);
}
void double_to_string(long double val, char *ret, flags f) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < f.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((f.is_precision_set && f.precision != 0) || (int)r ||
      (!f.is_precision_set && val == 0) || s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buff[idx + 1];
  }
}
void parse_mantiss(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';

  if ((int)val - val) {
    while ((int)val == 0) {
      pow++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }

  if (!f.is_precision_set) f.precision = 6;
  double_to_string(val, buff, f);
  prepend_mantiss(buff, pow, sign);
  format_flags(buff, f);
}

void prepend_mantiss(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

void parse_float_g_G(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }
  if (val == 0) {
    // Выводим ноль как "0.0"
    s21_strcpy(buff, "0.0");
    return;
  }

  if (!f.is_precision_set) {
    f.precision = 6;
  }
  if (f.precision == 0) f.precision = 1;
  int precision = f.precision;

  double_to_string(val, buff, f);
  format_gG_precision(buff, precision);
  format_flags(buff, f);
}

void format_gG_precision(char *buff, int precision) {
  int sig_digs = 0;
  s21_size_t len = s21_strlen(buff);
  int not_zero_found = 0;
  for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
    if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
      continue;
    else
      not_zero_found = 1;

    if (s21_isdigit(buff[i]) && not_zero_found) {
      sig_digs++;
    }
    if (sig_digs == precision && i + 1 < len) {
      int next = buff[i + 1] == '.' ? 2 : 1;
      buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
      buff[i + 1] = '\0';
      break;
    }
  }
}
