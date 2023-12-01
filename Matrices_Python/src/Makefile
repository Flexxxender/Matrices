TEST_LIB = tests
GCOV_LIB = report
SRC = src
AUTO_TEST = python3 -m pytest

all_tests: clean
	$(AUTO_TEST) $(TEST_LIB)/

coverage_tests: clean
	$(AUTO_TEST) --cov=$(SRC) $(TEST_LIB)/ -k "not time" -v

gcov_report: clean
	$(AUTO_TEST) --cov-report=html:$(GCOV_LIB) --cov=$(SRC) $(TEST_LIB)/ -k "not time" -v

time_tests: clean
	$(AUTO_TEST) -vv $(TEST_LIB)/test_time_matrix.py

clean:
	rm -rf .coverage report .pytest_cache .benchmarks __pycache__ tests/__pycache__