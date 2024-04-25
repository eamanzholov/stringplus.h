#include "s21_test_2.h"

#include <check.h>
#include <string.h>

#include "s21_string.h"

//  ***************************************
//  *************** STRLEN ****************
//  ***************************************

START_TEST(test_for_strlen_1) {
  const char *samples[] = LOREM_IPSUM;
  const char *str = samples[_i];
  ck_assert_uint_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_for_strlen_2) {
  char test_str[50][5] = {"\0", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++) {
        int s21_c = s21_strlen(test_str[i]);
        int s_c = strlen(test_str[i]);
        ck_assert_uint_eq(s21_c, s_c);
      }
}
END_TEST

//  ***************************************
//  *************** STRNCHR ***************
//  ***************************************

START_TEST(test_for_strchr_1) {
  char example = 'i';
  const char *samples[] = LOREM_IPSUM, *str = samples[_i];
  ck_assert_ptr_eq(strchr(str, example), s21_strchr(str, example));
}
END_TEST

//  ***************************************
//  *************** STRNCAT ***************
//  ***************************************

START_TEST(test_for_strncat) {
  char *s21_result;
  char *str_result;
  char buffer[100] = {" "};
  char s21_buffer[100] = {" "};

  char *test_array[3] = {"\0", "\t", "\n"};
  int len_array[5] = {0, 0.1, 1, 10};
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      for (int k = 0; k < 10; k++) {
        s21_result = s21_strncat(s21_buffer, test_array[_i], len_array[_i]);
        str_result = strncat(buffer, test_array[_i], len_array[_i]);
        ck_assert_str_eq(s21_result, str_result);
      }
}
END_TEST

//  ***************************************
//  *************** STRNCMP ***************
//  ***************************************

START_TEST(test_for_strncmp) {
  char test_str[50][20] = {"\0", "\t", "\n"};
  s21_size_t num[5] = {0, 0.1, 1, 10};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 4; k++) {
        int s21_c = s21_strncmp(test_str[i], test_str[j], num[k]);
        int s_c = strncmp(test_str[i], test_str[j], num[k]);
        if (s21_c > 0)
          s21_c = 1;
        else if (s21_c < 0)
          s21_c = -1;
        if (s_c > 0)
          s_c = 1;
        else if (s_c < 0)
          s_c = -1;
        ck_assert_int_eq(s21_c, s_c);
      }
}
END_TEST

Suite *s21_string_suite_2() {
  Suite *s1 = suite_create("Tests_for_string_2");

  TCase *tc_strlen = tcase_create("Tests_for_strlen ");
  TCase *tc_strncat = tcase_create("Tests_for_strncat ");
  TCase *tc_strchr = tcase_create("Tests_for_strchr ");
  TCase *tc_strncmp = tcase_create("Tests_for_strncmp ");

  suite_add_tcase(s1, tc_strlen);
  suite_add_tcase(s1, tc_strncat);
  suite_add_tcase(s1, tc_strchr);
  suite_add_tcase(s1, tc_strncmp);

  // strlen
  tcase_add_test(tc_strlen, test_for_strlen_1);
  tcase_add_test(tc_strlen, test_for_strlen_2);

  // strchr
  tcase_add_test(tc_strchr, test_for_strchr_1);

  // strncat
  tcase_add_test(tc_strncat, test_for_strncat);

  // strncmp
  tcase_add_test(tc_strncmp, test_for_strncmp);

  return s1;
}
