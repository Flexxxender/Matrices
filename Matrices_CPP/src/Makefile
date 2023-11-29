GCC = g++
CFLAGS = -Wall -Werror -Wextra
TESTLIB = ./tests/
MAIN = Matrix.cpp
OBJ_MAIN = Matrix.o
REPORT_FILE = test.info

TESTFILE = MainTests.cpp
OUT_TESTFILE = MainTests.out

TIME_TESTFILE = TimeTests.cpp
OUT_TIME_TESTFILE = TimeTests.out


build: $(MAIN)
	$(GCC) -c $(CFLAGS) -lstdc++ -std=c++17 $(MAIN) -o $(OBJ_MAIN)

clean:
	rm -rf *.o *.out unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: clean
	$(GCC) -lstdc++ -std=c++17 --coverage $(TESTLIB)$(TESTFILE) $(MAIN) -o $(OUT_TESTFILE) -lgtest
	valgrind --tool=memcheck --leak-check=yes  ./$(OUT_TESTFILE)

coverage_tests: clean
	$(GCC) -lstdc++ -std=c++17 --coverage $(TESTLIB)$(TESTFILE) $(MAIN) -o $(OUT_TESTFILE) -lgtest
	./$(OUT_TESTFILE)

time_tests: clean
	$(GCC) -lstdc++ -std=c++17 --coverage $(TESTLIB)$(TIME_TESTFILE) $(MAIN) -o $(OUT_TIME_TESTFILE) -lgtest
	./$(OUT_TIME_TESTFILE)

gcov_report: clean
	$(GCC) --coverage $(TESTLIB)$(TESTFILE) $(MAIN) -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -c -d ./ -o $(REPORT_FILE)
	lcov -r $(REPORT_FILE) "/usr*" -o $(REPORT_FILE)
	genhtml -o report $(REPORT_FILE)

format:
	-mv ../materials/.clang-format ./
	clang-format -n ./*.cpp ./*/*.cpp ./*.h
	clang-format -i ./*.cpp ./*/*.cpp ./*.h
	clang-format -n ./*.cpp ./*/*.cpp ./*.h
	-mv ./.clang-format ../materials/
