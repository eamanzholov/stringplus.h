#include <check.h>
#include <string.h>

#include "s21_sprintf_test.h"
#include "s21_sscanf_test.h"
#include "s21_string.h"
#include "s21_test_2.h"

START_TEST(test_for_memchr_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *s21_res = s21_memchr(test_str[i], test_str[j][0], num[k]);
              char *str_res = memchr(test_str[i], test_str[j][0], num[k]);
              ck_assert((s21_res == s21_NULL && str_res == s21_NULL) ||
                        (s21_res != s21_NULL && str_res != s21_NULL &&
                         s21_res == str_res));
            }
}
END_TEST

START_TEST(test_for_memchr_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *s21_res = s21_memchr(test_str[i], test_str[j][0], num[k]);
              char *str_res = memchr(test_str[i], test_str[j][0], num[k]);
              ck_assert((s21_res == s21_NULL && str_res == s21_NULL) ||
                        (s21_res != s21_NULL && str_res != s21_NULL &&
                         s21_res == str_res));
            }
}
END_TEST

START_TEST(test_for_memcmp_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              int s21_res = s21_memcmp(test_str[i], test_str[j], num[k]);
              int str_res = memcmp(test_str[i], test_str[j], num[k]);
              ck_assert_int_eq(s21_res, str_res);
            }
}
END_TEST

START_TEST(test_for_memcmp_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              int s21_res = s21_memcmp(test_str[i], test_str[j], num[k]);
              int str_res = memcmp(test_str[i], test_str[j], num[k]);
              ck_assert_int_eq(s21_res, str_res);
            }
}
END_TEST

START_TEST(test_for_memcpy) {
  char *s21_res, *str_res, *test_str[10] = {"\0", "\t", "\n"};
  char s21_buffer[100] = {" "}, buffer[100] = {" "};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_res = s21_memcpy(s21_buffer, test_str[j], num[k]);
              str_res = memcpy(buffer, test_str[j], num[k]);
              ck_assert_str_eq(s21_res, str_res);
            }
}
END_TEST

START_TEST(test_for_memset) {
  char *s21_res, *str_res, test_str[3][10] = {"\0", "\t", "\n"};
  char s21_buffer[100] = {" "}, buffer[100] = {" "};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_res = s21_memset(s21_buffer, test_str[j][0], num[k]);
              str_res = memset(buffer, test_str[j][0], num[k]);
              ck_assert_str_eq(s21_res, str_res);
            }
}
END_TEST

START_TEST(test_for_strncpy) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char s21_dest[100] = {0};
              char std_dest[100] = {0};
              s21_strncpy(s21_dest, test_str[i], num[k]);
              strncpy(std_dest, test_str[i], num[k]);
              ck_assert_str_eq(s21_dest, std_dest);
            }
}
END_TEST

START_TEST(test_for_strcspn_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_set[3][10] = {"abc", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_size_t s21_res = s21_strcspn(test_str[i], test_set[j]);
              s21_size_t std_res = strcspn(test_str[i], test_set[j]);
              ck_assert_int_eq(s21_res, std_res);
            }
}
END_TEST

START_TEST(test_for_strcspn_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_set[3][10] = {"abc", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_size_t s21_res = s21_strcspn(test_str[i], test_set[j]);
              s21_size_t std_res = strcspn(test_str[i], test_set[j]);
              ck_assert_int_eq(s21_res, std_res);
            }
}
END_TEST

START_TEST(test_for_strpbrk_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_set[3][10] = {"abc", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *s21_res = s21_strpbrk(test_str[i], test_set[j]);
              char *std_res = strpbrk(test_str[i], test_set[j]);
              ck_assert(
                  (s21_res == NULL && std_res == NULL) ||
                  (s21_res != NULL && std_res != NULL && s21_res == std_res));
            }
}
END_TEST

START_TEST(test_for_strpbrk_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_set[3][10] = {"abc", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *s21_res = s21_strpbrk(test_str[i], test_set[j]);
              char *std_res = strpbrk(test_str[i], test_set[j]);
              ck_assert(
                  (s21_res == NULL && std_res == NULL) ||
                  (s21_res != NULL && std_res != NULL && s21_res == std_res));
            }
}
END_TEST

START_TEST(test_for_strerror) {
  for (int i = -1000; i < 1000; i++) {
    char *got = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(got, expected);
  }
}
END_TEST

START_TEST(test_for_insert) {
  const char *src[] = {"Hello, world!", "Hello, world!", "Hello, world!"};
  const char *str[] = {"Check", s21_NULL, "Check"};
  s21_size_t start_index[] = {13, 6, 20};
  const char *expected[] = {"Hello, world!Check", s21_NULL, s21_NULL};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *result = s21_insert(src[i], str[i], start_index[i]);
              if (expected[i] == s21_NULL) {
                ck_assert_ptr_null(result);
              } else {
                ck_assert_str_eq(result, expected[i]);
                free(result);
              }
            }
}
END_TEST

START_TEST(test_for_trim) {
  const char *src[] = {" YaLomalstekloH B  ", "GarryPotter228 genderBOY", "",
                       " GarryPotter228! * > @ < genderBOY",
                       "#@# ()****) #@       "};
  const char *trim_chars[] = {" ", "GY", "528741", " GaY", "#@ "};
  const char *expected[] = {"YaLomalstekloH B", "arryPotter228 genderBO", "",
                            "rryPotter228! * > @ < genderBO", "()****)"};

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      for (int k = 0; k < 5; k++)
        for (int l = 0; l < 5; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              char *result = s21_trim(src[i], trim_chars[i]);
              ck_assert_str_eq(result, expected[i]);
              free(result);
            }
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s1 = suite_create("Tests_for_string");

  TCase *tc_memchr = tcase_create("Tests_for_memchr ");
  TCase *tc_memcmp = tcase_create("Tests_for_memcmp ");
  TCase *tc_memcpy = tcase_create("Tests_for_memcpy ");
  TCase *tc_memset = tcase_create("Tests_for_memset ");
  TCase *tc_strncpy = tcase_create("Tests_for_strncpy ");
  TCase *tc_strcspn = tcase_create("Tests_for_strcspn ");
  TCase *tc_strpbrk = tcase_create("Tests_for_strpbrk ");
  TCase *tc_strerror = tcase_create("Tests_for_strerror ");
  TCase *tc_insert = tcase_create("Tests_for_insert ");
  TCase *tc_trim = tcase_create("Tests_for_trim ");
  TCase *tc_atoi = tcase_create("Tests_for_atoi ");
  TCase *tc_memmove = tcase_create("Tests_for_memmove ");
  TCase *tc_strcat = tcase_create("Tests_for_strcat ");

  // Добавление тестового case в тестовый suite
  suite_add_tcase(s1, tc_memchr);
  suite_add_tcase(s1, tc_memcmp);
  suite_add_tcase(s1, tc_memcpy);
  suite_add_tcase(s1, tc_memset);
  suite_add_tcase(s1, tc_strncpy);
  suite_add_tcase(s1, tc_strcspn);
  suite_add_tcase(s1, tc_strpbrk);
  suite_add_tcase(s1, tc_strerror);
  suite_add_tcase(s1, tc_insert);
  suite_add_tcase(s1, tc_trim);
  suite_add_tcase(s1, tc_atoi);
  suite_add_tcase(s1, tc_memmove);
  suite_add_tcase(s1, tc_strcat);

  // Добавление тестов в тестовый case
  tcase_add_test(tc_memchr, test_for_memchr_1);
  tcase_add_test(tc_memchr, test_for_memchr_2);
  tcase_add_test(tc_memcmp, test_for_memcmp_1);
  tcase_add_test(tc_memcmp, test_for_memcmp_2);
  tcase_add_test(tc_memcpy, test_for_memcpy);
  tcase_add_test(tc_memset, test_for_memset);
  tcase_add_test(tc_strncpy, test_for_strncpy);
  tcase_add_test(tc_strcspn, test_for_strcspn_1);
  tcase_add_test(tc_strcspn, test_for_strcspn_2);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_1);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_2);
  tcase_add_test(tc_strerror, test_for_strerror);
  tcase_add_test(tc_insert, test_for_insert);
  tcase_add_test(tc_trim, test_for_trim);

  return s1;
}

int main() {
  Suite *s, *s1, *s2, *s3;
  SRunner *runner, *runner1, *runner2, *runner3;

  s = s21_string_suite();
  s1 = s21_string_suite_2();
  s2 = s21_sprintf_suite();
  s3 = s21_sscanf_suite();
  runner = srunner_create(s);
  runner1 = srunner_create(s1);
  runner2 = srunner_create(s2);
  runner3 = srunner_create(s3);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_set_fork_status(runner1, CK_NOFORK);
  srunner_set_fork_status(runner2, CK_NOFORK);
  srunner_set_fork_status(runner3, CK_NOFORK);
  // Запуск всех тестов
  srunner_run_all(runner, CK_NORMAL);
  srunner_run_all(runner1, CK_NORMAL);
  srunner_run_all(runner2, CK_NORMAL);
  srunner_run_all(runner3, CK_NORMAL);

  srunner_free(runner);
  srunner_free(runner1);
  srunner_free(runner2);
  srunner_free(runner3);

  return 0;
}