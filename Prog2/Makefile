#Makefile Program2

TORM = opcodetab.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings


opcodetab.o:	opcodetab.cc opcodetab.h opcode_error_exception.h
	${CC} ${CCFLAGS} -c opcodetab.cc

clean:
	rm -f ${TORM}
