#include "fila.h"

/* cria uma fila de tamanho max N*/
Queue * create_queue(int tam){
	Queue * q;
	q = malloc(sizeof(Queue));
	q->v = malloc(tam*sizeof(Queue));
	q->begin = 0;
	q->end = 0;
	q->size = 0;
	q->N = tam;
	return q;
}

/* adiciona o jogador p no final da fila q */
void queue(Queue * q, Player * p){
	q->v[q->end] = p;
	/* utiliza modulo, uma vez end passa do tamanho ela volta ao inicio */
	q->end =(q->end + 1) % q->N;
	q->size ++;
}

/* retira da fila q o jogador que está lá há mais tempo*/
Player * dequeue(Queue * q){
	Player * p;
	p = q->v[q->begin];
	/* utiliza modulo, uma vez begin passa do tamanho ela volta ao inicio */
	q->begin = (q->begin + 1) % q->N;
	q->size --;
	return p;
}

/* destroí a fila q*/
void destroy_queue(Queue * q){
	free(q->v);
	free(q);
}
