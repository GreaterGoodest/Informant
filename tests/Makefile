CC = gcc
CFLAG = -Wall -g
INCLUDE = -I ../include
LIBS = -lcmocka
WRAP = -Wl,--wrap=puts

test_print_usage: test_print_usage.c
	$(CC) $(CFLAG) $(WRAP) test_print_usage.c ../library/helpers.c $(INCLUDE) $(LIBS) -o test_print_usage