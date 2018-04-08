#include "pilha.h"

void push(Stack * stack, int x){
	Alegoria_node * new = malloc(sizeof(Alegoria_node));
	/* atribuí o número da alegoria ao novo elemento */
	new->alegoria = x;
	/* adiciona novo elemento a pilha */
	new->next = stack->top;
	stack->top = new;
}

int pop(Stack * stack){
	Alegoria_node * top = stack->top;
	int x = top->alegoria;
	stack->top = stack->top->next;
	free(top);
	/* retorna o número da alegoria desempilhada */
	return x;
}

Stack * create_stack(){
	Stack * stack = malloc(sizeof(Stack));
	stack->top = NULL;
	return stack;
}

void destroy_stack(Stack * stack){
	free(stack);
}

int check_top(Stack * stack){
	/* se não tiver topo retorna 0*/
	if (stack->top == NULL){
		return 0;
	}
	/* retorna o número da alegora no topo*/
	return stack->top->alegoria;
}