CC = gcc
OBJS = main.o
CFLAG = -Wall -g
INCLUDE =
LIBS = 

informant: ${OBJS}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

bin:
	mkdir bin