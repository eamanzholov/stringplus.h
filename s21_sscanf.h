#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_
#include "s21_string.h"

#if defined(VERBOSE_MODE) && defined(DEBUG)
typedef enum specifier {
  NONE_SPEC,
  CHAR,
  DECIMAL,
  INT,
  SCI_e,
  SCI_E,
  FLOAT,
  SHORT_FLOAT_g,
  SHORT_FLOAT_G,
  UNSIGNED_OCT,
  STR,
  UNSIGNED_DEC_INT,
  UNSIGNED_HEX_x,
  UNSIGNED_HEX_X,
  POINTER_ADDR,
  N_OF_SCANNED_CHARS_UNTIL_N_OCCURS,
  PERCENT_CHAR
} specifier;
#endif

typedef enum width_t { NONE_WIDTH, WIDTH_NUMBER, WIDTH_AST } width_t;

typedef enum length_t {
  NONE_LENGTH,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} length_t;

typedef struct token {
  void *addr;  // Address of corresponding vararg pointer
  // %[width][.precision][length][specifier]
  width_t width;
  unsigned int width_n;

  length_t length_t;

  char buff[512];
  char spec;
} token;

int s21_sscanf(const char *str, const char *format, ...);

/* (0) Helper functions */
int has_trailing_whitespace(const char *src);
void write_chars_to_buffer(char **src, const char *allowed_chars, char *buffer,
                           int16_t width, int start_index);
unsigned long long int parse_str_to_unsigned_long_long(const char *string,
                                                       char **endptr, int basis,
                                                       int n_byte);
int s21_isspace(char c);
void convert_unsigned_type(token *unsigned_token, unsigned long long int result,
                           int sign);
void convert_integer_type(token *integer_token, long long int result, int sign);
void convert_float_type(token *float_token, long double result);
int s21_isalpha(char c);

token extract_format_token(char **fstr, va_list *va);

void process_width_specifier(char **fstr, token *tok);
void process_length_modifier(char **fstr, token *tok);
void process_specifier(char **fstr, token *tok);
int get_number_from_format_string(char **fstr);

void skip_whitespace(char **src);
void skip_matched_buffer_characters(char **src, int *fail, token *tok);

void format_output(char **src, token *tokens, int tok_len, int *res);
void write_char_from_string(char **src, int *result_count, token *tok,
                            int *fail_flag);
void write_integer_to_memory(char **src, int *fail, int *result_count,
                             token *tok);
void write_unspecified_int_to_memory(char **src, int *fail_flag,
                                     int *result_count, token *tok);
void write_float_value_to_memory(char **src, int *result, token *float_token);
void write_string_value_to_memory(char **src, const int *fail_flag, int *result,
                                  token *string_token);
void write_unsigned_value_to_memory(char **src, int *fail_flag, int *result,
                                    token *unsigned_token);
void write_integer_from_hex_or_oct_to_memory(char **src, int *fail_flag,
                                             int *result, token *integer_token,
                                             int base);
long double convert_to_long_double(const char *buffer);

#endif  // SRC_S21_SSCANF_H_