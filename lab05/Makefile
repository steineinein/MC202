TARGET = main
CC = gcc
GFLAGS = -ansi -Wall -pedantic-errors -Werror -g -lm

all: $(TARGET)

$(TARGET): lab05.o pilha.o
	$(CC) lab05.o pilha.o -o $(TARGET) $(GFLAGS)

lab05.o: lab05.c
	$(CC) lab05.c -c $(GFLAGS)

pilha.o: pilha.c pilha.h
	$(CC) pilha.c -c $(GFLAGS)

clean:
	rm -f  *.o
