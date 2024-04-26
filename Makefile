CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -fprofile-arcs -ftest-coverage
TEST_SRC= s21_test.c s21_test_2.c s21_sprintf_test.c s21_sscanf_test.c
TEST_FLAGS= -lcheck_pic -pthread -lrt -lm -lsubunit

all: clean s21_string.a test gcov_report

s21_string.a:
	$(CC) -c s21_string.c -o s21_string.o $(CFLAGS)
	$(CC) -c s21_strerror.c -o s21_strerror.o $(CFLAGS)
	$(CC) -c s21_sprintf.c -o s21_sprintf.o $(CFLAGS)
	$(CC) -c s21_sscanf.c -o s21_sscanf.o $(CFLAGS)
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: 
	$(CC) $(CFLAGS) ${TEST_SRC} s21_string.a -o s21_test ${TEST_FLAGS} -fsanitize=address -g
	./s21_test

gcov_report: test
	mkdir -p report
	mv *.gcda *.gcno report/
	~/.local/bin/gcovr -r . --html --html-details -o report/index.html 
	open report/index.html

	
clean:
	rm -rf *.o *.a s21_test *.gcno *.gcda *.info report *.gcov


# gcov_report:
#     gcov s21_test.c s21_test_2.c
#     $(CC) $(CFLAGS) s21_test.c s21_test_2.c s21_string.a -o test -lcheck_pic -pthread -lrt -lm -lsubunit -fsanitize=address -g
#     ./test
#     mkdir -p report
#     mv *.gcov report/
# ~/.local/bin/gcovr -r . --html --html-details -o report/index.html --gcov-ignore-parse-errors

# valgrind --tool=memcheck --leak-check=yes  ./s21_test
# valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./s21_test
# gcc -fprofile-arcs -ftest-coverage s21_memchr_test.c s21_string.a -o test_linux -lcheck_pic -pthread -lrt -lm -lsubunit
# cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
# clang-format -i *.c *.h
# -fsanitize=address -g