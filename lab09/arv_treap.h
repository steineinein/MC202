#ifndef ARV_TREAP_H
#define ARV_TREAP_H
#include <stdlib.h>
#include <stdio.h>

/* struct de uma transação em aravóre treap, onde o banco é a chave
e valor o valor da transação*/
typedef struct Treap{
	long banco;
	double valor;
	int prioriade;
	struct Treap * dir, * esq;
}no_treap;

/* cria uma Treap vazia */
no_treap * criar_treap();

/* busca um uma transação do banco */
no_treap * busca(no_treap * raiz, long banco);

/* insere uma nova transação do banco com valor determinado */
no_treap * inserir(no_treap * raiz, long banco, double valor);

/* remove uma transação do banco*/
no_treap * deletar(no_treap * raiz, long banco);

/* encontra o banco com menor identificador*/
double minimo(no_treap * raiz);

/*imprime a arvóre inteira */
void print_arvore(no_treap * raiz);

#endif