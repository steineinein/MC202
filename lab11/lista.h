#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* estrutura de um nó de uma lista, cujo o dado é um inteiro*/
typedef struct no{
    int v;
    struct no * prox;
} No;

/* cria uma lista vazia */
No * criar_lista();

/* destroi a lista */
void destruir_lista(No * lista);

/* adiciona um novo elemento a lista e retorna a nova lista */
No * insere_na_lista(No * lista, int v);

/* remove o elemento v da lista */
No * remove_da_lista(No * list, int v);

void imprimir_lista(No* lista);

#endif