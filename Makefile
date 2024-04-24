CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -fprofile-arcs -ftest-coverage

all: clean s21_string.a test gcov_report

s21_string.a:
	$(CC) -c s21_string.c -o s21_string.o $(CFLAGS)
	$(CC) -c s21_strerror.c -o s21_strerror.o $(CFLAGS)
	$(CC) -c s21_sprintf.c -o s21_sprintf.o $(CFLAGS)
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: 
	$(CC) $(CFLAGS) s21_test.c s21_test_2.c s21_sprintf_test.c s21_string.a -o s21_test -lcheck_pic -pthread -lrt -lm -lsubunit -fsanitize=address -g
	./s21_test

gcov_report:
	./s21_test
	mkdir -p report
	gcov *.c
	gcov *.gcda report/
	mv *.gcov report/
	~/.local/bin/gcovr -r . --html --html-details -o report/index.html --gcov-ignore-parse-errors
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

# valgrind --tool=memcheck --leak-check=yes  ./main.out
# gcc -fprofile-arcs -ftest-coverage s21_memchr_test.c s21_string.a -o test_linux -lcheck_pic -pthread -lrt -lm -lsubunit
# cppcheck --enable=all --suppress=missingIncludeSystem 
# clang-format -i s21_test.c s21_string.c s21_string.h s21_strerror.c
# -fsanitize=address -g