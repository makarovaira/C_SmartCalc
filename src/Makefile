CC+FLAGS = gcc -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -L. --coverage -ls21_smartcalc
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -pthread -lrt -lsubunit
	OPEN_CMD = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = open
endif

all: install

install: uninstall build
	mv build/Calculator.app .
	rm -rf build/*
	rm -rf build/.qmake.stash
	mv Calculator.app build/

build:
	mkdir build
	cd ./build/ && qmake ../ && make

uninstall:
	rm -rf build

run:
ifeq ($(OS), Linux)
	./build/Calculator.app
else
	open build/Calculator.app
endif

dvi:
	makeinfo description.texi --html
	$(OPEN_CMD) ./description/index.html

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir ../Archive_SmartCalc_v1.0/
	mkdir ../Archive_SmartCalc_v1.0/src
	cp -rf * ../Archive_SmartCalc_v1.0/src
	mv ../Archive_SmartCalc_v1.0/ .
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/

test: s21_smartcalc.a
	$(CC+FLAGS) calc_tests.c s21_smartcalc.a $(CHECK_FLAGS) -L. -ls21_smartcalc -o unit_test
	./unit_test

gcov_report: s21_smartcalc.a
	$(CC+FLAGS) s21_smart_calc.c calc_tests.c s21_smartcalc.a $(CHECK_FLAGS) $(GCOVFLAGS) -o unit_test
	./unit_test
	lcov -t unit_test -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html
	make clean_test

s21_smartcalc.a: s21_smart_calc.o
	ar rcs libs21_smartcalc.a *.o
	rm -rf *.o
	ranlib libs21_smartcalc.a
	cp libs21_smartcalc.a s21_smartcalc.a
	cp libs21_smartcalc.a ls21_smartcalc.a

s21_smart_calc.o:
	$(CC+FLAGS) -c s21_smart_calc.c

check-linters:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h *.cpp
	rm -f .clang-format

clean_obj:
	rm -rf *.o *.a

clean_test: clean_obj
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf unit_test

clean: clean_test
	rm -rf mem_check.txt
	rm -rf report
	rm -rf manual

rebuild: clean uninstall all

reinstall: clean uninstall install