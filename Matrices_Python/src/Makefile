DEL_LINUX_FLAGS = rm -rf
CHECK_WIN_FLAG = if exist
DEL_WIN_FLAGS = /s /q
AUTO_TEST = pytest
TEST_LIB = tests
GCOV_LIB = coverage_html
SRC = src

ifeq ($(OS),Windows_NT)
	del_coverage = $(CHECK_WIN_FLAG) .coverage del .coverage
	del_coverage_html = $(CHECK_WIN_FLAG) coverage_html rmdir $(DEL_WIN_FLAGS) coverage_html
	del_cache = $(CHECK_WIN_FLAG) .pytest_cache rmdir $(DEL_WIN_FLAGS) .pytest_cache
	del_benchmarks = $(CHECK_WIN_FLAG) .benchmarks rmdir $(DEL_WIN_FLAGS) .benchmarks
else
	del_coverage = $(DEL_LINUX_FLAGS) .coverage
	del_coverage_html = $(DEL_LINUX_FLAGS) coverage_html
	del_cache = $(DEL_LINUX_FLAGS) .pytest_cache
	del_benchmarks = $(DEL_LINUX_FLAGS) .benchmarks
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
	$(del_coverage_html)
	$(del_cache)
	$(del_benchmarks)