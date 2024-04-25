#include <check.h>
#include <string.h>

#include "s21_sprintf_test.h"
#include "s21_sscanf_test.h"
#include "s21_string.h"
#include "s21_test_2.h"

// memchr
START_TEST(test_for_memchr_1) {
  char str[30] = "123qwer143";
  ck_assert_pstr_eq(s21_memchr(str, '3', 13), memchr(str, '3', 13));
  ck_assert_pstr_eq(s21_memchr(str, 'e', 13), memchr(str, 'e', 13));
}
END_TEST

START_TEST(test_for_memchr_2) {
  char str[30] = "123qwer143";
  ck_assert_pstr_eq(s21_memchr(str, 'c', 29), memchr(str, 'c', 29));
}
END_TEST

START_TEST(test_for_memchr_3) {
  char str[30] = "@\\%^&  ";
  ck_assert_pstr_eq(s21_memchr(str, '@', 5), memchr(str, '@', 5));
  ck_assert_pstr_eq(s21_memchr(str, 92, 5), memchr(str, 92, 5));
  ck_assert_pstr_eq(s21_memchr(str, ' ', 5), memchr(str, ' ', 5));
}
END_TEST

START_TEST(test_for_memchr_4) {
  char str[30] = "123qwer143";
  ck_assert_pstr_eq(s21_memchr(str, 'r', 5), memchr(str, 'r', 5));
  ck_assert_pstr_eq(s21_memchr(str, 4, 5), memchr(str, 4, 5));
}
END_TEST

START_TEST(test_for_memchr_5) {
  char str[30] = "\0";
  ck_assert_pstr_eq(s21_memchr(str, '\0', 5), memchr(str, '\0', 5));
}
END_TEST

// memcmp
START_TEST(test_for_memcmp_1) {
  char str[30] = "123qwer143";
  char str1[30] = "123qwer143";
  ck_assert_int_eq(s21_memcmp(str, str1, 5), memcmp(str, str1, 5));
  char str4[30] = "zxcd";
  char str5[30] = "zxcd";
  ck_assert_int_eq(s21_memcmp(str4, str5, 5), memcmp(str4, str5, 5));
  char str2[30] = "zxcd";
  char str3[30] = "ZXCD";
  ck_assert_int_eq(s21_memcmp(str2, str3, 0), memcmp(str2, str3, 0));
}
END_TEST

START_TEST(test_for_memcmp_2) {
  char str2[30] = "123Qwer143";
  char str3[30] = "123Q";
  ck_assert_int_eq(s21_memcmp(str2, str3, 7), memcmp(str2, str3, 7));
  char str4[30] = "123Q";
  char str5[30] = "123Qwer143";
  ck_assert_int_eq(s21_memcmp(str4, str5, 7), memcmp(str4, str5, 7));
}
END_TEST

START_TEST(test_for_memcmp_3) {
  char str2[30] = "123Qwer143";
  char str3[30] = "123q";
  ck_assert_int_eq(s21_memcmp(str2, str3, 4), memcmp(str2, str3, 4));
  char str4[30] = "123qwer143";
  char str5[30] = "123Q";
  ck_assert_int_eq(s21_memcmp(str4, str5, 4), memcmp(str4, str5, 4));
  char str7[30] = "123qwer143";
  char str8[30] = "123q";
  ck_assert_int_eq(s21_memcmp(str7, str8, 4), memcmp(str7, str8, 4));
  char str9[30] = "123Qwer143";
  char str10[30] = "123Q";
  ck_assert_int_eq(s21_memcmp(str9, str10, 4), memcmp(str9, str10, 4));
}
END_TEST

START_TEST(test_for_memcmp_4) {
  char *str1 = "atoms\0\0\0\0";
  char *str2 = "atoms\0abc";
  ck_assert_int_eq(s21_memcmp(str1, str2, 7), memcmp(str1, str2, 7));
}
END_TEST

// memcpy
START_TEST(test_for_memcpy_1) {
  char str[30] = "123qwer143";
  char str1[30] = "";
  char str2[30] = "";
  s21_memcpy(str1, str, 5);
  memcpy(str2, str, 5);
  ck_assert_pstr_eq(str1, str2);
  char str3[30] = "123qwer143";
  char str4[30] = "";
  char str5[30] = "";
  s21_memcpy(str4, &str3[4], 5);
  memcpy(str5, &str3[4], 5);
  ck_assert_pstr_eq(str4, str5);
  char str6[30] = "123qwer144";
  char str7[30] = "";
  char str8[30] = "";
  s21_memcpy(str7, &str6[4], 10);
  memcpy(str8, &str6[4], 10);
  ck_assert_pstr_eq(str7, str8);
}
END_TEST

START_TEST(test_for_memcpy_2) {
  char str[30] = "123qwer143";
  char str1[30] = "";
  char str2[30] = "";
  s21_memcpy(str1, str, 0);
  memcpy(str2, str, 0);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_for_memcpy_3) {
  char str[30] = "123qwer143";
  char str1[30] = "";
  char str2[30] = "";
  s21_memcpy(str1, str, 15);
  memcpy(str2, str, 15);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// memset
START_TEST(test_for_memset_1) {
  char str[30] = "123qwer143";
  char str1[30] = "123qwer143";
  s21_memset(str, 't', 4);
  memset(str1, 't', 4);
  ck_assert_pstr_eq(str, str1);
}
END_TEST

START_TEST(test_for_memset_2) {
  char str[30] = "123qwer143";
  char str1[30] = "123qwer143";
  s21_memset(str, 't', 10);
  memset(str1, 't', 10);
  ck_assert_pstr_eq(str, str1);
}
END_TEST

START_TEST(test_for_memset_3) {
  char str[30] = "123qwer143";
  char str1[30] = "123qwer143";
  s21_memset(str, '\0', 4);
  memset(str1, '\0', 4);
  ck_assert_pstr_eq(str, str1);
}
END_TEST

START_TEST(test_for_memset_4) {
  char str[30] = "123qwer143";
  char str1[30] = "123qwer143";
  s21_memset(str, 67, 15);
  memset(str1, 67, 15);
  ck_assert_pstr_eq(str, str1);
}
END_TEST

// strncpy
START_TEST(test_for_strncpy_1) {
  char str[30] = "xxxxxxxxxx";
  char str1[30] = "123qwer143";
  ck_assert_pstr_eq(s21_strncpy(str, str1, 5), strncpy(str, str1, 5));
}
END_TEST

START_TEST(test_for_strncpy_2) {
  char str[30] = "xxxxxxxxxx";
  char str1[30] = "\0";
  ck_assert_pstr_eq(s21_strncpy(str, str1, 1), strncpy(str, str1, 1));
}
END_TEST

// strcspn
START_TEST(test_for_strcspn_1) {
  char str[30] = "qwerty";
  char str1[30] = "rty";
  char str2[30] = "uio";
  char str3[30] = "tyr";
  ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
  ck_assert_int_eq(s21_strcspn(str, str2), strcspn(str, str2));
  ck_assert_int_eq(s21_strcspn(str, str3), strcspn(str, str3));
}
END_TEST

START_TEST(test_for_strcspn_2) {
  char str[30] = "qwerty";
  char str1[30] = "wq";
  char str2[30] = "qwer";
  ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
  ck_assert_int_eq(s21_strcspn(str, str2), strcspn(str, str2));
}
END_TEST

START_TEST(test_for_strcspn_3) {
  char str[30] = "qwerty";
  char str1[30] = "\0";
  ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
}
END_TEST

// strpbrk
START_TEST(test_for_strpbrk_1) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "u2134";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_2) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "zxcvf";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_3) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_4) {
  char str[30] = "\0";
  char str1[30] = "23e4";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_5) {
  char str[30] = "\0";
  char str1[30] = "23e\04";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_6) {
  char *str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *str2 = "12345Z67890";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_pstr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
}
END_TEST

// strerror
START_TEST(test_for_strerror) {
  ck_assert_str_eq(s21_strerror(_i), strerror(_i));

  // const char *got = s21_strerror(-1);
  // char *expected = strerror(-1);
  // ck_assert_str_eq(got, expected);

  for (int i = -1000; i < 135; i++) {
    char *got = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(got, expected);
  }
}
END_TEST

// insert
START_TEST(test_for_insert_1) {
  const char *src = "Hello, world!";
  const char *str = "Check";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  char *expected = "CheckHello, world!";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_for_insert_2) {
  const char *src = "Hello, world!";
  const char *str = "Check";
  s21_size_t start_index = 6;
  char *result = s21_insert(src, str, start_index);
  char *expected = "Hello,Check world!";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_for_insert_3) {
  const char *src = "Hello, world!";
  const char *str = "Check";
  s21_size_t start_index = 13;
  char *result = s21_insert(src, str, start_index);
  char *expected = "Hello, world!Check";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_for_insert_4) {
  const char *src = "Hello, world!";
  const char *str = NULL;
  s21_size_t start_index = 6;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_for_insert_5) {
  const char *src = "Hello, world!";
  const char *str = "Check";
  s21_size_t start_index = 20;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_for_insert_6) {
  const char *src = "Hello, world!";
  const char *str = "Check";
  s21_size_t start_index = 6;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_ne(result, src);
  ck_assert_ptr_ne(result, str);
  free(result);
}

END_TEST

// trim
START_TEST(test_for_trim_1) {
  char *str = "0005555000";
  char *result_1 = s21_trim(str, "0");
  ck_assert_str_eq(result_1, "5555");
  free(result_1);

  char *result_2 = s21_trim(str, "05");
  ck_assert_str_eq(result_2, "");
  free(result_2);
}
END_TEST

START_TEST(test_for_trim_2) {
  char *str = "asdfghjkl ,. asdfghjkl";
  char *result_1 = s21_trim(str, " ,.");
  ck_assert_str_eq(result_1, "asdfghjkl ,. asdfghjkl");
  free(result_1);

  char *result_2 = s21_trim(str, "asdfghjkl");
  ck_assert_str_eq(result_2, " ,. ");
  free(result_2);
}
END_TEST

START_TEST(test_for_trim_3) {
  char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *result_1 = s21_trim(str, " ,.");
  ck_assert_str_eq(result_1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(result_1);

  char *result_2 = s21_trim(str, "ABC");
  ck_assert_str_eq(result_2, "DEFGHIJKLMNOPQRSTUVWXYZ");
  free(result_2);

  char *result_3 = s21_trim(str, "A");
  ck_assert_str_eq(result_3, "BCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(result_3);

  char *result_4 = s21_trim(str, "Z");
  ck_assert_str_eq(result_4, "ABCDEFGHIJKLMNOPQRSTUVWXY");
  free(result_4);

  char *result_5 = s21_trim(str, "XYZ");
  ck_assert_str_eq(result_5, "ABCDEFGHIJKLMNOPQRSTUVW");
  free(result_5);

  char *result_6 = s21_trim(str, "ABCXYZ");
  ck_assert_str_eq(result_6, "DEFGHIJKLMNOPQRSTUVW");
  free(result_6);
}
END_TEST

START_TEST(test_for_trim_4) {
  char *str1 = " 777 ";
  char *result_1 = s21_trim(str1, " ");
  ck_assert_str_eq(result_1, "777");
  free(result_1);

  char *str2 = "";
  char *result_2 = s21_trim(str2, s21_NULL);
  ck_assert_str_eq(result_2, "");
  free(result_2);
}
END_TEST

START_TEST(test_for_atoi_1) {
  char src[] = "  +123123123";
  ck_assert_int_eq(atoi(src), s21_atoi(src));
}
END_TEST

START_TEST(test_for_memmove_1) {
  char src[200] = "";
  char src2[200] = "";
  s21_size_t copy_kByte = 0;

  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 0;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_2) {
  char src[200] = "123SDFAZ`ESFsdfsdf";
  char src2[200] = "123SDFAZ`ESFsdfsdf";
  s21_size_t copy_kByte = 10;

  char res[200] = "";
  char expected[200] = "";
  s21_size_t check_kByte = 10;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_3) {
  char src[200] = "";
  char src2[200] = "";
  s21_size_t copy_kByte = 0;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 13;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_4) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_5) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res + 13, src, copy_kByte);
  memmove(expected + 13, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_6) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  s21_size_t copy_kByte = 4;

  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_size_t check_kByte = 17;

  s21_memmove(res + 5, src, copy_kByte);
  memmove(expected + 5, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_7) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_8) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src + 17;
  char *expected = src2 + 17;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_9) {
  char src[200] = "I HATE memmove!!!";
  char src2[200] = "I HATE memmove!!!";
  s21_size_t copy_kByte = 17;

  char *res = src + 5;
  char *expected = src2 + 5;
  s21_size_t check_kByte = 34;

  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);

  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(test_for_memmove_10) {
  char src[] = "aboba";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_11) {
  char src[] = "";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_12) {
  char src[] = "I hate memcmp";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_13) {
  char src[] = "123";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_14) {
  char src[] = "aboba";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_15) {
  char src[] = "Zboba";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_16) {
  char src[] = "09";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_17) {
  char src[] = "abobasdafoijasdofjas asdopij";
  s21_size_t kByte = 28;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_18) {
  char src[] = "aposkd AOSIjFasodijpaoisdjf poisdjfg";
  s21_size_t kByte = 36;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_19) {
  char src[] = "aodasf ieuwfh luhasdfLIAUSHD liuh 12li3uh 12i4ouhsdfh";
  s21_size_t kByte = 53;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_20) {
  char src[] =
      "()()(((())):!,....aodasf ieuwfh luhasdfLIAUSHD liuh 12li3uh 12i4ouhsdfh";
  s21_size_t kByte = 71;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_21) {
  int src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_size_t kByte = 4;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_memmove_22) {
  float src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_size_t kByte = 8;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memmove(res, src, kByte);
  memmove(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_for_strcat_1) {
  char src[] = " aboba!!!";
  char res[5 + 10] = "Hello";
  char expected[5 + 10] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_for_strcat_2) {
  char src[] = " aboba!!!";
  char res[0 + 10] = "";
  char expected[0 + 10] = "";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_for_strcat_3) {
  char src[] = "";
  char res[] = "Hello";
  char expected[] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_for_strcat_4) {
  char src[] = "asdfj  asdf aisdfjaiushdfASD SAD asDSad ASDAsdwqqeAS";
  char res[5 + 53] = "Hello";
  char expected[5 + 53] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_for_strcat_5) {
  char src[] = "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS";
  char res[5 + 59] = "Hello";
  char expected[5 + 59] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_for_strcat_6) {
  char src[] =
      "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS)(?!.,";
  char res[5 + 65] = "Hello";
  char expected[5 + 65] = "Hello";

  s21_strcat(res, src);
  strcat(expected, src);

  ck_assert_str_eq(res, expected);
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
  // memchr
  tcase_add_test(tc_memchr, test_for_memchr_1);
  tcase_add_test(tc_memchr, test_for_memchr_2);
  tcase_add_test(tc_memchr, test_for_memchr_3);
  tcase_add_test(tc_memchr, test_for_memchr_4);
  tcase_add_test(tc_memchr, test_for_memchr_5);

  // memcmp
  tcase_add_test(tc_memcmp, test_for_memcmp_1);
  tcase_add_test(tc_memcmp, test_for_memcmp_2);
  tcase_add_test(tc_memcmp, test_for_memcmp_3);
  tcase_add_test(tc_memcmp, test_for_memcmp_4);

  // memcpy
  tcase_add_test(tc_memcpy, test_for_memcpy_1);
  tcase_add_test(tc_memcpy, test_for_memcpy_2);
  tcase_add_test(tc_memcpy, test_for_memcpy_3);

  // memset
  tcase_add_test(tc_memset, test_for_memset_1);
  tcase_add_test(tc_memset, test_for_memset_2);
  tcase_add_test(tc_memset, test_for_memset_3);
  tcase_add_test(tc_memset, test_for_memset_4);

  // strncpy
  tcase_add_test(tc_strncpy, test_for_strncpy_1);
  tcase_add_test(tc_strncpy, test_for_strncpy_2);

  // strcspn
  tcase_add_test(tc_strcspn, test_for_strcspn_1);
  tcase_add_test(tc_strcspn, test_for_strcspn_2);
  tcase_add_test(tc_strcspn, test_for_strcspn_3);

  // strpbrk
  tcase_add_test(tc_strpbrk, test_for_strpbrk_1);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_2);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_3);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_4);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_5);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_6);

  // strerror
  tcase_add_test(tc_strerror, test_for_strerror);

  // insert
  tcase_add_test(tc_insert, test_for_insert_1);
  tcase_add_test(tc_insert, test_for_insert_2);
  tcase_add_test(tc_insert, test_for_insert_3);
  tcase_add_test(tc_insert, test_for_insert_4);
  tcase_add_test(tc_insert, test_for_insert_5);
  tcase_add_test(tc_insert, test_for_insert_6);

  // trim
  tcase_add_test(tc_trim, test_for_trim_1);
  tcase_add_test(tc_trim, test_for_trim_2);
  tcase_add_test(tc_trim, test_for_trim_3);
  tcase_add_test(tc_trim, test_for_trim_4);

  // atoi
  tcase_add_test(tc_atoi, test_for_atoi_1);

  // memmove
  tcase_add_test(tc_memmove, test_for_memmove_1);
  tcase_add_test(tc_memmove, test_for_memmove_2);
  tcase_add_test(tc_memmove, test_for_memmove_3);
  tcase_add_test(tc_memmove, test_for_memmove_4);
  tcase_add_test(tc_memmove, test_for_memmove_5);
  tcase_add_test(tc_memmove, test_for_memmove_6);
  tcase_add_test(tc_memmove, test_for_memmove_7);
  tcase_add_test(tc_memmove, test_for_memmove_8);
  tcase_add_test(tc_memmove, test_for_memmove_9);
  tcase_add_test(tc_memmove, test_for_memmove_10);
  tcase_add_test(tc_memmove, test_for_memmove_11);
  tcase_add_test(tc_memmove, test_for_memmove_12);
  tcase_add_test(tc_memmove, test_for_memmove_13);
  tcase_add_test(tc_memmove, test_for_memmove_14);
  tcase_add_test(tc_memmove, test_for_memmove_15);
  tcase_add_test(tc_memmove, test_for_memmove_16);
  tcase_add_test(tc_memmove, test_for_memmove_17);
  tcase_add_test(tc_memmove, test_for_memmove_18);
  tcase_add_test(tc_memmove, test_for_memmove_19);
  tcase_add_test(tc_memmove, test_for_memmove_20);
  tcase_add_test(tc_memmove, test_for_memmove_21);
  tcase_add_test(tc_memmove, test_for_memmove_22);
  

  // strcat
  tcase_add_test(tc_strcat, test_for_strcat_1);
  tcase_add_test(tc_strcat, test_for_strcat_2);
  tcase_add_test(tc_strcat, test_for_strcat_3);
  tcase_add_test(tc_strcat, test_for_strcat_4);
  tcase_add_test(tc_strcat, test_for_strcat_5);
  tcase_add_test(tc_strcat, test_for_strcat_6);

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
