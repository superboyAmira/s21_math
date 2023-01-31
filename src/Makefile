# Common
SYS = $(shell uname)
CC = gcc
FLAGS = -Wall -Wextra -Werror
LEAKS = nothing
SRCS = s21_math.c
OBJS = $(SRCS:.c=.o)

# Library
LIB_NAME = libs21_math.a
LIB_FLAGS = -lcheck -lm -lpthread

# Testing
TEST_NAME = test_s21math.c
TEST_FLAGS_GCOV = -fprofile-arcs -ftest-coverage # они нужны для покрытия пользовательского простарнства, но мне они не понадобились

ifeq ($(SYS), Darwin) # Проверяем ОС
	LIB_FLAGS = -lcheck
	LEAKS = leaks --atExit -- test
else
	LIB_FLAGS = -lcheck -lsubunit -pthread -lrt -lm
	LEAKS = CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif

all: clean s21_math.a test gcov_report

s21_math.a: clean
	$(CC) -c $(SRCS) $(shell pkg-config --libs --cflags check) # указывается путь до библитеки check.h
	ar rc $(LIB_NAME) $(OBJS) # нужно для запаковки всех скомпилированных файлов в библиотеку.а Опция c заставляет создавать (от create) библиотеку, если ее нет, а опция r (от replace) заменяет старые объектные файлы новыми версиями.
	ranlib $(LIB_NAME)
clean:
	rm -rf test_lib ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./math_o ./*.dSYM ./test_s21math ./CPPLINT* test

test: s21_math.a
	# проверка создания статической библиотеки libs21_math.a
	$(CC) $(FLAGS) -c $(TEST_NAME) -o test.o $(shell pkg-config --libs --cflags check) # компилим любой сишник
	$(CC) $(FLAGS) -c $(SRCS) -o $(OBJS) $(shell pkg-config --libs --cflags check) # компилим нашу библиотеку
	$(CC) test.o $(OBJS) -L. -ls21_math -o test_lib $(shell pkg-config --libs --cflags check)
	# проверка корректности функций
	$(CC) $(FLAGS) --coverage $(TEST_NAME) $(SRCS) $(LIB_NAME) $(LIB_FLAGS) -o gcov_test $(shell pkg-config --libs --cflags check)
	chmod +x *
	./gcov_test

gcov_report: s21_math.a
	$(CC) $(FLAGS) --coverage $(TEST_NAME) $(SRCS) $(LIB_NAME) $(LIB_FLAGS) -o gcov_test $(shell pkg-config --libs --cflags check)
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d . # -t отвечает за имя теста https://stackoverflow.com/questions/837639/is-there-a-way-to-focus-lcov-code-coverage-reports-to-just-one-or-two-directorie
	genhtml -o report/ gcov_test.info # генерирует html страницу
	open ./report/index.html

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h *.c
	rm -rf CPPLINT.cfg
	clang-format -style=google -i *.c *.h
	clang-format -style=google -n *.c *.h
	make test
rebuild: clean all
	open ./report/index.html