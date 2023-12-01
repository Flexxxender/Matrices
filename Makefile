MAKE = make
CPP_DIR = -C ./Matrices_CPP/src
PYTHON_DIR = -C ./Matrices_Python/src


clean:
	$(MAKE) $(CPP_DIR) clean
	$(MAKE) $(PYTHON_DIR) clean


python_report:
	$(MAKE) $(PYTHON_DIR) gcov_report

cpp_report:
	$(MAKE) $(CPP_DIR) gcov_report

report: python_report cpp_report


python_coverage:
	$(MAKE) $(PYTHON_DIR) coverage_tests

cpp_coverage:
	$(MAKE) $(CPP_DIR) coverage_tests	
	
coverage: python_coverage cpp_coverage


python_time:
	$(MAKE) $(PYTHON_DIR) time_tests

cpp_time:
	$(MAKE) $(CPP_DIR) time_tests	
	
time: python_time cpp_time


cpp_leaks:
	$(MAKE) $(CPP_DIR) leaks