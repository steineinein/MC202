#ifndef PILHA_H
#define PILHA_H
#include <stdlib.h>
#include <stdio.h>
#endif

/* lista ligada das alegorias */
typedef struct alegoria_node{
	int alegoria;
	struct alegoria_node * next;
} Alegoria_node;

/* pilha das alegorias */
typedef struct {
	Alegoria_node * top;
} Stack;

/* recebe um inteiro que representa o número a alegoria e empilha*/
void push(Stack * stack, int x);

/* desempilha um elemento, devolver o número da alegoria desenpilhada*/
int pop(Stack * stack);

/* cria pilha */
Stack * create_stack();

/* detroi a pilha*/
void destroy_stack(Stack * stack);

/* olha o topo da pilha*/
int check_top(Stack * stack);