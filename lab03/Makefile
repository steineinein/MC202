CC=gcc
GFLAGS=-ansi -Wall -Werror -pedantic-errors -g -lm

all: main

main: lista.o memoria.o lab03.c
	$(CC) lab03.c lista.o memoria.o -o main $(GFLAGS)

lista.o: lista.c lista.h
	$(CC) lista.c -c $(GFLAGS)

memoria.o: memoria.c memoria.h
	$(CC) memoria.c -c $(GFLAGS)

clean:
	rm -f *.o

