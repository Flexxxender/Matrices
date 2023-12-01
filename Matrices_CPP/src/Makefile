GCC = g++
CFLAGS = -Wall -Werror -Wextra
TESTLIB = ./tests/
MAIN = Matrix.cpp
OBJ_MAIN = Matrix.o
LIB_MAIN = Matrix.a
REPORT_FILE = test.info

TESTFILE = MainTests.cpp
OUT_TESTFILE = MainTests.out

TIME_TESTFILE = TimeTests.cpp
OUT_TIME_TESTFILE = TimeTests.out

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Darwin) 
	LEAKS = leaks -atExit -- ./$(OUT_TESTFILE)
endif
ifeq ($(UNAME_S),Linux)
	LEAKS = valgrind --tool=memcheck --leak-check=yes ./$(OUT_TESTFILE)
endif

all: $(LIB_MAIN)

build: $(MAIN)
	$(GCC) -c $(CFLAGS) -lstdc++ -std=c++17 $(MAIN) -o $(OBJ_MAIN)

Matrix.a: build
	ar rcs $(LIB_MAIN) $(OBJ_MAIN)
	ranlib $(LIB_MAIN)

clean:
	rm -rf *.out *.gcda *.gcno *.info report gcov_report *.a

rebuild:
	make clean
	make build

leaks: coverage_tests
	$(LEAKS)

coverage_tests: clean $(LIB_MAIN)
	$(GCC) -lstdc++ -std=c++17 --coverage $(TESTLIB)$(TESTFILE) $(LIB_MAIN) -o $(OUT_TESTFILE) -lgtest
	./$(OUT_TESTFILE)

time_tests: clean $(LIB_MAIN)
	$(GCC) -lstdc++ -std=c++17 --coverage $(TESTLIB)$(TIME_TESTFILE) $(LIB_MAIN) -o $(OUT_TIME_TESTFILE) -lgtest
	./$(OUT_TIME_TESTFILE)

gcov_report: clean
	$(GCC) --coverage $(TESTLIB)$(TESTFILE) $(MAIN) -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -c -d ./ -o $(REPORT_FILE)
	lcov -r $(REPORT_FILE) "/usr*" -o $(REPORT_FILE)
	genhtml -o report $(REPORT_FILE)
	rm -rf *.out *.gcda *.gcno *.info gcov_report *.o

format:
	-mv ../materials/.clang-format ./
	clang-format -n ./*.cpp ./*/*.cpp ./*.h
	clang-format -i ./*.cpp ./*/*.cpp ./*.h
	clang-format -n ./*.cpp ./*/*.cpp ./*.h
	-mv ./.clang-format ../materials/
