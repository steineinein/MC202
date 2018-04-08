#ifndef FILA_H
#define FILA_H
#include <stdlib.h>
#include "participante.h"
#endif

/* estrutura de uma fila circular de jogadores
 sendo v um vetor de ponteiro para jogadores */
typedef struct{
	Player **v;
	int begin, end, N, size;
} Queue;

/* cria uma fila de tamanho max N*/
Queue * create_queue(int N);

/* adiciona o jogador p no final da fila q */
void queue(Queue* q, Player * p);

/* retira da fila q o jogador que está lá há mais tempo*/
Player * dequeue(Queue* q);

/* destroí a fila q*/
void destroy_queue(Queue* q);
