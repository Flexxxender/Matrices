DEL_LINUX_FLAGS = rm -rf
CHECK_WIN_FLAG = if exist
DEL_WIN_FLAGS = /s /q
AUTO_TEST = pytest
TEST_LIB = tests
GCOV_LIB = report
SRC = src

ifeq ($(OS),Windows_NT)
	del_coverage = $(CHECK_WIN_FLAG) .coverage del .coverage
	del_report = $(CHECK_WIN_FLAG) report rmdir $(DEL_WIN_FLAGS) report
	del_cache = $(CHECK_WIN_FLAG) .pytest_cache rmdir $(DEL_WIN_FLAGS) .pytest_cache
	del_benchmarks = $(CHECK_WIN_FLAG) .benchmarks rmdir $(DEL_WIN_FLAGS) .benchmarks
	del__pycache__1 = $(CHECK_WIN_FLAG) __pycache__ rmdir $(DEL_WIN_FLAGS) __pycache__
	del__pycache__2 = $(CHECK_WIN_FLAG) tests\__pycache__ rmdir $(DEL_WIN_FLAGS) tests\__pycache__
else
	del_coverage = $(DEL_LINUX_FLAGS) .coverage
	del_report = $(DEL_LINUX_FLAGS) report
	del_cache = $(DEL_LINUX_FLAGS) .pytest_cache
	del_benchmarks = $(DEL_LINUX_FLAGS) .benchmarks
	del__pycache__1 = $(DEL_LINUX_FLAGS) __pycache__
	del__pycache__2 = $(DEL_LINUX_FLAGS) tests\__pycache__
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