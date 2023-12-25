CC = g++ 
CFLAGS = -Wall -Werror -Wextra -g -lstdc++ -std=c++17
TESTFLAGS = -lcheck -coverage -lpthread -pthread 
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage

ifeq ($(shell uname), Linux)
    LDFLAGS += -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    OPEN_CMD := open
endif

all: clean s21_matrix_oop.a

clean: 
	rm -rf *.o *.a *.gcno *gcda report *.info  *.out test test.dSYM

test: 
	$(CC) s21_matrix_test.cc s21_matrix.cc $(CFLAGS) -pthread -lgtest -o test
	./test

s21_matrix_oop.a: s21_matrix.cc
	$(CC) $(CFLAGS) -c s21_matrix.cc
	ar -rv s21_matrix_oop.a s21*.o s21_matrix_oop.h
	ranlib s21_matrix_oop.a

style:
	clang-format -style=Google -n  *.cc *.h 

leaks:
	leaks --atExit -- ./test
	
valgrind: 
	valgrind --tool=memcheck --leak-check=yes ./test

rebuild: clean all