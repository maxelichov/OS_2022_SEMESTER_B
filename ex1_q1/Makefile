


CFLAGS = -Wall -c
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex1_q1
all: $(PROG) test

ex1_q1: ex1_q1.o
	${CC} ${CCFLAGS} ex1_q1.o -o ex1_q1

ex1_q1.o:       ex1_q1.c        ex1_q1.h
	$(CC) $(CFLAGS) ex1_q1.c -lm

clean:
	rm -vf *.o ${PROG} *.log *merged

test:
	@echo going to run test...
	./${PROG} grades_1.txt grades_2.txt

	
	
	
