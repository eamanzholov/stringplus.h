#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *fstr, ...) {
  int eof_fl = has_trailing_whitespace(str), res = 0;

  if (!eof_fl) {
    va_list va;
    va_start(va, fstr);
    int tokens_len = 0;

    char *formstr = (char *)fstr;
    int len = (int)s21_strlen(formstr);
    char *src = (char *)str;

    token tokens[BUFF_SIZE];

    while (*formstr && formstr < fstr + len && tokens_len < BUFF_SIZE) {
      tokens[tokens_len] = extract_format_token(&formstr, &va);
      tokens_len++;
    }

    format_output(&src, tokens, tokens_len, &res);
    va_end(va);
  }

  return (eof_fl) ? eof_fl : res;
}

int s21_isspace(char c) { return (c == ' ' || c == '\n' || c == '\t'); }

int s21_isalpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int has_trailing_whitespace(const char *src) {
  int result = -1;

  for (int i = 0; src[i]; i++) {
    if (!s21_isspace(src[i]) && src[i] != '\0') {
      result = 0;
      break;
    }
  }

  return result;
}

token extract_format_token(char **fstr, va_list *va) {
  token tok = {.addr = s21_NULL,
               .length_t = NONE_LENGTH,
               .spec = 0,
               .width = NONE_WIDTH,
               .width_n = 0};

  if (s21_isspace(**fstr)) {
    tok.spec = 'z';
    skip_whitespace(fstr);
  }

  if (**fstr == '%' && !tok.spec) {
    (*fstr)++;

    if (**fstr == '%') {
      s21_memset(tok.buff, '\0', BUFF_SIZE - 1);
      tok.buff[0] = '%';
      (*fstr)++;
      tok.spec = 'b';
    } else {
      process_width_specifier(fstr, &tok);
      process_length_modifier(fstr, &tok);
      process_specifier(fstr, &tok);

      if (tok.width != WIDTH_AST) tok.addr = va_arg(*va, void *);
    }

    if (tok.spec == 'p') tok.length_t = NONE_LENGTH;
  }

  if (s21_isalpha(**fstr) && !tok.spec) {
    s21_memset(tok.buff, '\0', BUFF_SIZE - 1);
    int i = 0;
    while (**fstr && !s21_isspace(**fstr) && **fstr != '%') {
      tok.buff[i++] = **fstr;
      (*fstr)++;
    }
    tok.spec = 'b';
  }

  return tok;
}

void skip_matched_buffer_characters(char **src, int *fail, token *tok) {
  int test = s21_strspn(*src, tok->buff);
  int len = s21_strlen(tok->buff);

  if (len == 1 && **src == tok->buff[0]) {
    (*src) = (*src) + len;
    return;
  }

  if (test != len)
    *fail = 1;
  else
    (*src) = (*src) + len;
}

void process_width_specifier(char **fstr, token *tok) {
  if (**fstr == '*') {
    (*fstr)++;
    tok->width = WIDTH_AST;
  } else {
    int res = get_number_from_format_string(fstr);

    if (res) {
      tok->width = WIDTH_NUMBER;
      tok->width_n = res;
    }
  }
}

int get_number_from_format_string(char **fstr) {
  char tmp[BUFF_SIZE] = {'\0'};

  int res = 0, i = 0;

  while (**fstr >= '0' && **fstr <= '9') {
    tmp[i] = **fstr;
    (*fstr)++;
    i++;
  }

  res = s21_atoi(tmp);

  return res;
}

void process_length_modifier(char **fstr, token *tok) {
  switch (**fstr) {
    case 'h':
      tok->length_t = LENGTH_SHORT;
      (*fstr)++;
      break;
    case 'l':
      tok->length_t = LENGTH_LONG;
      (*fstr)++;
      if (**fstr == 'l') {
        tok->length_t = LENGTH_LONG_LONG;
        (*fstr)++;
      }
      break;
    case 'L':
      tok->length_t = LENGTH_LONG_DOUBLE;
      (*fstr)++;
      break;
  }
}

void process_specifier(char **fstr, token *tok) {
  tok->spec = (**fstr);
  (*fstr)++;
}

void format_output(char **src, token *tokens, int tok_len, int *res) {
  char *start = *src;

  for (int i = 0, fail = 0; i < tok_len && !fail; i++) {
    char spec = tokens[i].spec;
    if (spec == 'c') write_char_from_string(src, res, (tokens + i), &fail);
    if (spec == 'd') write_integer_to_memory(src, &fail, res, (tokens + i));
    if (spec == 'i' || spec == 'p')
      write_unspecified_int_to_memory(src, &fail, res, (tokens + i));
    if (spec == 'g' || spec == 'G' || spec == 'f')
      write_float_value_to_memory(src, res, (tokens + i));
    if (spec == 's')
      write_string_value_to_memory(src, &fail, res, (tokens + i));
    if (spec == 'u')
      write_unsigned_value_to_memory(src, &fail, res, (tokens + i));
    if (spec == 'x' || spec == 'X')
      write_integer_from_hex_or_oct_to_memory(src, &fail, res, (tokens + i),
                                              16);
    if (spec == 'o')
      write_integer_from_hex_or_oct_to_memory(src, &fail, res, (tokens + i), 8);
    if (spec == 'n') *((int *)tokens[i].addr) = (*src) - start;
    if (spec == 'z') skip_whitespace(src);
    if (spec == 'b') skip_matched_buffer_characters(src, &fail, (tokens + i));
  }
}

void skip_whitespace(char **src) {
  while (**src && s21_isspace(**src)) {
    (*src)++;
  }
}

void write_char_from_string(char **src, int *result_count, token *tok,
                            int *fail_flag) {
  *fail_flag = 1;
  if (**src) {
    *fail_flag = 0;
    if (tok->width != WIDTH_AST) {
      *(char *)tok->addr = **src;
      (*result_count)++;
    }
    (*src)++;
  }
}

void write_integer_to_memory(char **src, int *fail, int *result_count,
                             token *tok) {
  char buffer[BUFF_SIZE] = {'\0'};
  *fail = 1;

  if (s21_strspn(*src, "0123456789+-")) {
    int sign_length = s21_strspn(*src, "+-");

    if (!(sign_length > 1 ||
          (sign_length && (tok->width_n <= 1 && tok->width)))) {
      buffer[0] = **src;
      (*src)++;
      write_chars_to_buffer(src, "0123456789", buffer, tok->width_n, 1);
      if (tok->width != WIDTH_AST) (*result_count)++;
      *fail = 0;
    }
  }

  if (!*fail) {
    long long int result = s21_atoi(buffer);
    if (tok->spec == 'p' && tok->width != WIDTH_AST) {
      unsigned long long int res_unsigned =
          parse_str_to_unsigned_long_long(buffer, NULL, 16, s21_strlen(buffer));
      *(int *)tok->addr = (int)res_unsigned;
    } else {
      if (tok->width != WIDTH_AST) convert_integer_type(tok, result, 1);
    }
  }
}

void write_unspecified_int_to_memory(char **src, int *fail_flag,
                                     int *result_count, token *tok) {
  *fail_flag = 1;
  skip_whitespace(src);

  if (s21_strspn(*src, "0x") == 2) {
    *fail_flag = 0;
    write_integer_from_hex_or_oct_to_memory(src, fail_flag, result_count, tok,
                                            16);
  } else if (s21_strspn(*src, "0") == 1) {
    *fail_flag = 0;
    write_integer_from_hex_or_oct_to_memory(src, fail_flag, result_count, tok,
                                            8);
  } else if (s21_strspn(*src, "+-0123456789")) {
    *fail_flag = 0;
    write_integer_to_memory(src, fail_flag, result_count, tok);
  }
}

void write_chars_to_buffer(char **src, const char *allowed_chars, char *buffer,
                           int16_t width, int start_index) {
  while (**src && s21_strspn(*src, allowed_chars) != 0) {
    // Проверка на превышение ширины или на пробельный символ для остановки
    if ((width && start_index >= width) || (s21_isspace(**src))) break;

    // Копирование символа в буфер, если указан
    if (buffer) buffer[start_index] = **src;

    (*src)++;
    start_index++;
  }
}

void write_float_value_to_memory(char **src, int *result, token *float_token) {
  int test = 0;

  if (float_token->spec == 'f')
    test = s21_strspn(*src, "0123456789+-");
  else
    test = s21_strspn(*src, "0123456789eE+-NnaAifIF");

  if (test) {
    int sign = s21_strspn(*src, "+-");
    if (!(sign > 1 ||
          (sign && (float_token->width_n <= 1 && float_token->width)))) {
      char buff[BUFF_SIZE] = {'\0'};
      int start_ind = 0;
      if (sign) {
        buff[0] = **src;
        start_ind = 1;
        (*src)++;
      }

      if (float_token->spec == 'f')
        write_chars_to_buffer(src, ".0123456789+-", buff, float_token->width_n,
                              start_ind);
      else
        write_chars_to_buffer(src, ".0123456789eE+-NnaAifIF", buff,
                              float_token->width_n, start_ind);

      if (float_token->width != WIDTH_AST) {
        long double res = convert_to_long_double(buff);
        (*result)++;
        convert_float_type(float_token, res);
      }
    }
  }

  if (float_token->width != WIDTH_NUMBER) {
    if (float_token->spec == 'f')
      write_chars_to_buffer(src, ".0123456789", s21_NULL, 0, 0);
    else
      write_chars_to_buffer(src, ".0123456789eE+-NaAifIFn", s21_NULL, 0, 0);
  }
}

void write_string_value_to_memory(char **src, const int *fail_flag, int *result,
                                  token *string_token) {
  int success = 0;
  char buffer[BUFF_SIZE] = {'\0'};
  unsigned int index = 0;

  while (**src != '\0' && !success && !(*fail_flag)) {
    if (!s21_isspace(**src)) {
      success = 1;
      while (**src != '\0' && !(*fail_flag)) {
        buffer[index] = **src;
        index++;

        if (string_token->width == WIDTH_NUMBER &&
            index >= string_token->width_n) {
          break;
        }

        (*src)++;

        if (s21_isspace(**src)) {
          (*src)--;
          break;
        }
      }
    }

    (*src)++;
  }

  if (string_token->width != WIDTH_AST && success) {
    s21_strcpy((char *)string_token->addr, buffer);
    (*result)++;
  }
}

void write_unsigned_value_to_memory(char **src, int *fail_flag, int *result,
                                    token *unsigned_token) {
  *fail_flag = 1;
  skip_whitespace(src);
  char buffer[BUFF_SIZE] = {'\0'};

  if (s21_strspn(*src, "0123456789+-")) {
    int sign = s21_strspn(*src, "+-");
    if (!((sign > 1 || (sign && (unsigned_token->width_n <= 1 &&
                                 unsigned_token->width))))) {
      *fail_flag = 0;
      buffer[0] = **src;
      (*src)++;

      write_chars_to_buffer(src, "0123456789", buffer, unsigned_token->width_n,
                            1);

      if (unsigned_token->width != WIDTH_AST) (*result)++;
    }
  }

  unsigned long long int result_value = s21_atoi(buffer);

  if (unsigned_token->width != WIDTH_AST && !*fail_flag)
    convert_unsigned_type(unsigned_token, result_value, 1);

  if (unsigned_token->width != WIDTH_NUMBER)
    write_chars_to_buffer(src, "0123456789", s21_NULL, 0, 0);
}

void write_integer_from_hex_or_oct_to_memory(char **src, int *fail_flag,
                                             int *result, token *integer_token,
                                             int base) {
  int sign = 1;
  char *ptr = s21_NULL;
  if (integer_token->spec == 'p') base = 16;

  skip_whitespace(src);
  if (**src == '-') {
    integer_token->width_n--;
    sign = -1;
    (*src)++;
  }
  if (base == 16 && **src == '0' && (*(*src + 1) == 'x' || *(*src + 1) == 'X'))
    integer_token->width_n -= 2;

  if (s21_strspn(*src, "0123456789abcdefABCDEF") > 0 ||
      s21_strspn(*src, "xX0123456789abcdefABCDEF") >= 2) {
    unsigned long long int result_value = parse_str_to_unsigned_long_long(
        *src, &ptr, base,
        integer_token->width ? integer_token->width_n : s21_strlen(*src));
    if (integer_token->width != WIDTH_AST) {
      *result += 1;

      if (integer_token->spec == 'p')
        *(int *)integer_token->addr = (int)result_value;
      else
        convert_unsigned_type(integer_token, result_value, sign);
    }
  } else {
    *fail_flag = 1;
  }
  unsigned int max = (unsigned int)s21_strspn(*src, "xX0123456789abcdefABCDEF");

  if (integer_token->width != WIDTH_NUMBER)
    *src += max;
  else
    *src += max < integer_token->width_n ? max : integer_token->width_n;
}

void convert_unsigned_type(token *unsigned_token, unsigned long long int result,
                           int sign) {
  if (unsigned_token->length_t == NONE_LENGTH) {
    *(unsigned int *)unsigned_token->addr = sign * (unsigned int)result;
  } else if (unsigned_token->length_t == LENGTH_SHORT) {
    *(unsigned short int *)unsigned_token->addr =
        sign * (unsigned short int)result;
  } else if (unsigned_token->length_t == LENGTH_LONG) {
    *(unsigned long int *)unsigned_token->addr =
        sign * (unsigned long int)result;
  } else if (unsigned_token->length_t == LENGTH_LONG_LONG) {
    *(unsigned long long int *)unsigned_token->addr =
        sign * (unsigned long long int)result;
  }
}

void convert_integer_type(token *integer_token, long long int result,
                          int sign) {
  if (integer_token->spec != 'p') {
    if (integer_token->length_t == NONE_LENGTH) {
      *(int *)integer_token->addr = sign * (int)result;
    } else if (integer_token->length_t == LENGTH_SHORT) {
      *(short int *)integer_token->addr = sign * (short int)result;
    } else if (integer_token->length_t == LENGTH_LONG) {
      *(long int *)integer_token->addr = sign * (long int)result;
    } else if (integer_token->length_t == LENGTH_LONG_LONG) {
      *(long long int *)integer_token->addr = sign * (long long int)result;
    }
  }
}

void convert_float_type(token *float_token, long double result) {
  if (float_token->length_t == NONE_LENGTH) {
    *(float *)float_token->addr = (float)result;
  } else if (float_token->length_t == LENGTH_LONG) {
    *(double *)float_token->addr = (double)result;
  } else if (float_token->length_t == LENGTH_LONG_DOUBLE) {
    *(long double *)float_token->addr = (long double)result;
  }
}

/**
 * @brief Преобразует строку в беззнаковое целое число с указанным основанием и
 * длиной.
 * @param string Строка для преобразования.
 * @param endptr Указатель на указатель на символ, в котором заканчивается
 * преобразование.
 * @param basis Основание системы счисления.
 * @param n_byte Максимальная длина строки для преобразования.
 * @return Беззнаковое целое число.
 */
unsigned long long int parse_str_to_unsigned_long_long(const char *string,
                                                       char **endptr, int basis,
                                                       int n_byte) {
  unsigned long long res = 0;
  short sign = 1;

  // Если указатель endptr не равен NULL, устанавливаем его в NULL.
  if (endptr) *endptr = s21_NULL;

  // Символы, используемые для преобразования.
  char dict[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Обработка знака числа.
  if (*string == '-') {
    sign = -1;
    string++;
  }

  // Обработка префикса 0x для шестнадцатеричного числа.
  if (basis == 16 &&
      (!s21_strncmp(string, "0x", 2) || !s21_strncmp(string, "0X", 2)))
    string += 2;

  // Парсинг строки.
  while (*string && n_byte) {
    char *tmp2;
    char current_sim =
        (*string >= 'a' && *string <= 'z') ? *string - 'a' + 'A' : *string;
    tmp2 = s21_strchr(dict, (int)current_sim);

    if (!tmp2) {
      break;  // Выход, если символ не найден в словаре.
    } else {
      // Получение числового значения текущего символа.
      long long val = (tmp2 - dict) / sizeof(char);

      // Проверка на соответствие основанию.
      if (val >= basis) {
        break;  // Выход, если значение больше основания.
      } else {
        res = res * basis + val;
        string++;
        n_byte--;
      }
    }
  }

  // Устанавливаем указатель endptr, если передан.
  if (endptr && *string) {
    *endptr = (char *)string;
  }

  return res * sign;
}

/**
 * @brief Ищет подстроку в строке без учета регистра символов.
 * @param buff Строка, в которой производится поиск.
 * @param pat Подстрока, которую нужно найти.
 * @return 1, если подстрока найдена, иначе 0.
 */
static int case_insensitive_search(const char *buff, const char *pat) {
  int found = 0;
  int len = (int)s21_strlen(pat);

  // Перебираем символы строки buff.
  for (int i = 0; buff[i] && !found; i++) {
    int counter = 0;

    // Сравниваем символы подстроки pat с соответствующими символами строки
    // buff.
    for (int j = 0; j < len; j++) {
      // Проверяем совпадение символов, игнорируя регистр.
      if ((buff[i] == (pat[j] - 'A') + 'a') ||
          (buff[i] == (pat[j] - 'a') + 'A') || pat[j] == buff[i]) {
        counter++;
        i++;  // Увеличиваем индекс строки buff.
      }

      // Если длина найденной подстроки равна длине pat, то подстрока найдена.
      if (len == counter) {
        found = 1;
        break;
      }
    }
  }

  return found;
}

/**
 * @brief Проверяет, содержит ли строка подстроки "inf" или "nan" (без учета
 * регистра символов).
 * @param buffer Строка для проверки.
 * @return 1, если строка содержит "inf" или "nan", иначе 0.
 */
static int includes_inf_nan(const char *buffer) {
  int result = 0;

  // Проверяем наличие подстрок "inf" и "nan" в строке buffer.
  int test1 = case_insensitive_search(buffer, "inf");
  int test2 = case_insensitive_search(buffer, "nan");

  // Если хотя бы одна из подстрок найдена, устанавливаем результат в 1.
  if (test1 || test2) {
    result = 1;
  }

  return result;
}

/**
 * @brief Возвращает INFINITY, если строка содержит подстроку "inf" (независимо
 * от регистра), и NAN, если строка содержит подстроку "nan" (независимо от
 * регистра).
 * @param buffer Строка для проверки.
 * @return INFINITY, если строка содержит "inf", NAN, если строка содержит
 * "nan", иначе 0.
 */
static long double return_nan_inf(const char *buffer) {
  int res = 0;

  // Проверяем наличие подстрок "inf" и "nan" в строке buffer.
  for (int i = 0; buffer[i]; i++) {
    if (buffer[i] == 'i' || buffer[i] == 'I') {
      res = 1;  // Нашли "inf"
      break;
    }

    if (buffer[i] == 'n' || buffer[i] == 'N') {
      res = 2;  // Нашли "nan"
      break;
    }
  }

  // Возвращаем INFINITY, если найдена подстрока "inf", и NAN, если найдена
  // подстрока "nan".
  return (res == 1) ? INFINITY : (res == 2) ? NAN : 0;
}

/**
 * @brief Применяет экспоненту к числу.
 * @param res Число, к которому применяется экспонента.
 * @param buffer Строка с экспонентой.
 * @return Результат применения экспоненты к числу.
 */
static long double apply_exponent(long double res, const char *buffer) {
  char sign = '+';  // Знак экспоненты
  int expon = 0;    // Экспонента

  // Поиск символа 'e' или 'E' для определения экспоненты
  for (const char *p = buffer; *p; p++) {
    if (*p == 'e' || *p == 'E') {
      sign = *(p + 1);          // Знак экспоненты
      expon = s21_atoi(p + 2);  // Экспонента
    }
  }

  // Применение экспоненты к числу
  while (expon) {
    if (sign == '-') {
      res /= 10.0;  // Если знак отрицательный, делим число на 10
    } else {
      res *= 10.0;  // Иначе умножаем число на 10
    }
    expon--;  // Уменьшаем значение экспоненты
  }

  return res;  // Возвращаем результат
}

/**
 * @brief Проверяет, содержит ли строка экспоненту.
 * @param buffer Строка для проверки.
 * @return 1, если экспонента найдена, иначе 0.
 */
static int includes_exponent(const char *buffer) {
  int res = 0;  // Изначально экспонента не найдена

  // Поиск символов 'e' или 'E' в строке
  for (const char *p = buffer; *p; p++) {
    if (s21_strspn(p, "eE")) {  // Если найден символ 'e' или 'E'
      res = 1;  // Устанавливаем результат в 1
      break;    // Прекращаем поиск
    }
  }

  return res;  // Возвращаем результат
}

/**
 * @brief Преобразует строку в число с плавающей точкой.
 * @param buffer Строка для преобразования.
 * @return Результат преобразования.
 */
static long double string_to_float(const char *buffer) {
  long double frac = 0.0;    // Дробная часть числа
  char *p = (char *)buffer;  // Указатель на начало строки
  int minus_flag = (*p == '-');  // Флаг минуса
  if (*p == '-' || *p == '+') p++;  // Пропускаем знак, если есть

  long double res = s21_atoi(p);  // Преобразуем целую часть строки в число

  while (s21_isdigit(*p)) p++;  // Пропускаем цифры целой части

  if (*p == '.') {  // Если есть десятичная точка
    p++;            // Пропускаем точку

    // Определяем количество нулей после десятичной точки
    int trailing_zeros = s21_strspn(p, "0");

    frac = s21_atoi(p);  // Преобразуем дробную часть в число
    int tmp = (int)frac;
    while (tmp) {
      frac /= 10.0;  // Переводим дробную часть в нормальный вид
      tmp /= 10;
    }
    while (trailing_zeros) {
      frac /= 10.0;  // Убираем нули после точки
      trailing_zeros--;
    }
  }

  res += frac;  // Суммируем целую и дробную части

  return minus_flag ? -res : res;  // Возвращаем результат с учетом знака
}

/**
 * @brief Преобразует строку в значение типа long double, обрабатывая особые
 * случаи, такие как Inf и NAN, и применяя показатель степени, если он
 * присутствует.
 *
 * @param buffer Указатель на входную строку.
 * @return long double Преобразованное значение.
 */
long double convert_to_long_double(const char *buffer) {
  long double res = 0.0;
  // Проверяем, содержит ли строка Inf или NAN
  int inf_nan = includes_inf_nan(buffer);

  // Если строка не представляет собой Inf или NAN
  if (!inf_nan) {
    // Преобразуем строку в число с плавающей запятой
    res = string_to_float(buffer);

    // Если строка содержит показатель степени, применяем его
    if (includes_exponent(buffer)) {
      res = apply_exponent(res, buffer);
    }
  }

  // Возвращаем Inf или NAN, если они присутствуют, иначе преобразованное
  // значение
  return (inf_nan) ? return_nan_inf(buffer) : res;
}
