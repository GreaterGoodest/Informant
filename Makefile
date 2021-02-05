CC = gcc
CFLAG = -Wall -g
INCLUDE = -I ./include
CMOCKA = -I ../cmocka/include -L../cmocka/src/ -lcmocka
LIBS = 

informant: main.c library/binary_parsing.c
	$(CC) $(CFLAG) main.c library/binary_parsing.c library/helpers.c -o informant $(INCLUDE)