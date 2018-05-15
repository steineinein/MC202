#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H
#include <stdlib.h>
#endif

typedef void* Item;

/* retorna 0 se prioridades os elementos são iguais
 * retorna <0 se primeiro elemento é menos que segundo
 * retorna >0 se segundo elemento é menor que primeiro*/
typedef int (*fcmp)(void*, void *);

/* item é um ponteiro para void que será definido no cliente */
typedef struct {
	Item * v;
	int n, tamanho;
	fcmp cmp;
} FP;

/* cria uma fila de prioridade de tamanho tam com função de comparação que
 * for definida no cliente*/
FP * criar_filaprio(int tam, fcmp cmp);
/* destroi a fila recebida*/
void destroir_filaprio(FP* fprio);
/* insere um item na fila de prioridades */
void inserir(FP * fprio, Item item);
/* extrai o item com maior prioridade */
Item extrair_maximo(FP * fprio);
/* retorna 1 se vazia e 0 se não */
int vazia (FP * fprio);
/* retorna 1 se cheia e 0 se não */
int cheia (FP * frpio);
