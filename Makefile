CC = gcc
OBJS = main.o binary_parsing.o
CFLAG = -Wall -g
INCLUDE = -I ./include
LIBS = 

informant: main.c library/binary_parsing.c
	$(CC) main.c library/binary_parsing.c -o informant $(INCLUDE)

bin:
	mkdir bin