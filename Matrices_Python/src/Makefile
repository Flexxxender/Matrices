CHECK_WIN_FLAG = if exist
DEL_WIN_FLAGS = /s /q
TEST_LIB = tests
GCOV_LIB = report
SRC = src

ifeq ($(OS),Windows_NT)
	AUTO_TEST = pytest
	DEL_FLAGS = /s /q
else
	AUTO_TEST = python3 -m pytest
	DEL_FLAGS = rm -rf
endif

ifeq ($(OS),Windows_NT)
	del_coverage = $(CHECK_WIN_FLAG) .coverage del .coverage
	del_report = $(CHECK_WIN_FLAG) report rmdir $(DEL_FLAGS) report
	del_cache = $(CHECK_WIN_FLAG) .pytest_cache rmdir $(DEL_FLAGS) .pytest_cache
	del_benchmarks = $(CHECK_WIN_FLAG) .benchmarks rmdir $(DEL_FLAGS) .benchmarks
	del__pycache__1 = $(CHECK_WIN_FLAG) __pycache__ rmdir $(DEL_FLAGS) __pycache__
	del__pycache__2 = $(CHECK_WIN_FLAG) tests\__pycache__ rmdir $(DEL_FLAGS) tests\__pycache__
else
	del_coverage = $(DEL_FLAGS) .coverage
	del_report = $(DEL_FLAGS) report
	del_cache = $(DEL_FLAGS) .pytest_cache
	del_benchmarks = $(DEL_FLAGS) .benchmarks
	del__pycache__1 = $(DEL_FLAGS) __pycache__
	del__pycache__2 = $(DEL_FLAGS) tests\__pycache__
endif

all_tests: clean
	$(AUTO_TEST) $(TEST_LIB)/

coverage_tests: clean
	$(AUTO_TEST) --cov=$(SRC) $(TEST_LIB)/ -k "not time" -v

gcov_report: clean
	$(AUTO_TEST) --cov-report=html:$(GCOV_LIB) --cov=$(SRC) $(TEST_LIB)/ -k "not time" -v

time_tests: clean
	$(AUTO_TEST) -vv $(TEST_LIB)/test_time_matrix.py

clean:
	$(del_coverage)
	$(del_report)
	$(del_cache)
	$(del_benchmarks)
	$(del__pycache__1)
	$(del__pycache__2)