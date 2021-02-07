CC = gcc
CFLAG = -Wall -g
INCLUDE = -I ../include
LIBS = -lcmocka
WRAP_USAGE = -Wl,--wrap=puts
TESTS = test_determine_type test_print_usage

.PHONY: run_tests

all: test_determine_type test_print_usage run_tests

test_print_usage: test_print_usage.c
	$(CC) $(CFLAG) $(WRAP_USAGE) test_print_usage.c ../library/helpers.c $(INCLUDE) $(LIBS) -o test_print_usage

test_determine_type: test_determine_type.c
	$(CC) $(CFLAG) test_determine_type.c ../library/binary_parsing.c $(INCLUDE) $(LIBS) -o test_determine_type

run_tests: $(TESTS)
	./test_print_usage
	./test_determine_type