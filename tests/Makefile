CC = gcc
CFLAG = -Wall -g
INCLUDE = -I ../include
LIBS = -lcmocka
WRAP_USAGE = -Wl,--wrap=puts
WRAP_LB = -Wl,--wrap=open,--wrap=perror,--wrap=memset,--wrap=lstat,--wrap=mmap,--wrap=close
TESTS = test_determine_type test_print_usage test_load_binary

.PHONY: run_tests, clean

all: test_determine_type test_print_usage test_load_binary run_tests

test_print_usage: test_print_usage.c
	$(CC) $(CFLAG) $(WRAP_USAGE) test_print_usage.c ../library/helpers.c $(INCLUDE) $(LIBS) -o test_print_usage

test_determine_type: test_determine_type.c
	$(CC) $(CFLAG) test_determine_type.c ../library/binary_parsing.c $(INCLUDE) $(LIBS) -o test_determine_type

test_load_binary: test_load_binary.c
	$(CC) $(CFLAG) $(WRAP_LB) test_load_binary.c ../library/binary_parsing.c $(INCLUDE) $(LIBS) -o test_load_binary

run_tests: $(TESTS)
	./test_print_usage
	./test_determine_type
	./test_load_binary

clean:
	rm $(TESTS)