CFLAGS = -Wall -Werror -Wextra
TESTLIB = ./tests
MAIN = Matrix
TESTFILE = MainTest


build: $(MAIN).cpp
	g++ -c $(CFLAGS) $(MAIN).cpp -o $(MAIN).o -lstdc++ -std=c++17 

clean:
	rm -rf *.o *.out
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: test
	valgrind --tool=memcheck --leak-check=yes ./unit_test.out

test: $(MAIN).o $(TESTLIB)/$(TESTFILE).cpp
	g++ --coverage $(MAIN).o $(TESTLIB)/$(TESTFILE).cpp -o unit_test.out -lgtest -lstdc++ -std=c++17
	./unit_test.out

gcov_report: clean
	g++ --coverage $(TESTLIB)/$(TESTFILE).cpp $(MAIN).cpp -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html