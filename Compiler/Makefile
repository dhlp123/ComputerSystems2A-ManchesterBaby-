# Douglas Parkinson
# Makefile for compilation usage

CC = g++
CFLAGS = -Wall -pedantic -Wextra

make: compiler.cpp
	${CC} -o Compiler ${CFLAGS} compiler.cpp compiler.h

run:
	./Compiler

clean:
	rm -f Compiler
