# Define required macros here
SHELL = /bin/bash

OBJS =  main.o factorial.o hello.o
CFLAG = -Wall -g -funwind-tables -rdynamic
CC = cc
INCLUDES =
LIBS = -lm

btexam:
bactrace:
	${CC} ${CFLAGS} -o $@ ${LIBS}

hello:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o core *.core

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<
