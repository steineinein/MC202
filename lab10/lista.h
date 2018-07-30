#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* estrutura de um nó de uma lista, cujo o dado é uma string*/
typedef struct no{
    char chave[51];
    struct no * prox;
} No;

/* cria uma lista vazia */
No * criar_lista();

/* destroi a lista */
void destruir_lista(No * lista);

/* adiciona um novo elemento a lista e retorna a nova lista */
No * adicionar_elemento(No * lista, char * chave);

/*No * remover_elemento(No * list, char * chave);
*/
/* procura um element na lista e devolver o nó que ele se encontra */
No * buscar_elemento(No * lista, char * chave);

void imprimir_lista(No * lista);

#endif