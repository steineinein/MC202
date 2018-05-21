#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

typedef struct No{
	/* nome da pessoa procurada*/
	char nome[21];
	/* flad se o nome deve ser impresso,
	e nivel de consanguinidade​ */
	int imprimir, cossang;
	struct No *esq, *dir;
} no;

/* criar um arvore genealogica contendo o nome das pessoas e seu graude de
consanguinidade​ com a raiz*/
no* criar_arvore(int h, int hmax);

/* procura uma pessoa especifica na arvóre*/
no* procurar_no(no* raiz, char* dado);

/* imprime as pessoas a serem imprimidas em pré ordem */
void pre_ordem(no* raiz);