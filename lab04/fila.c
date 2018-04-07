#include "fila.h"

Queue * create_queue(int tam){
	Queue * q;
	q = malloc(sizeof(Queue));
	q->v i= malloc(tam*sizeof(Queue));
	q->begin = 0;
	q->end = 0;
	q->size = 0;
	q->N = tam;
	return q;
}
void queue(Queue * q; Player * p){
	q->v[q->end] = p;
	q->end =(f->end + 1) % q->N;
	q->size ++;
}

Player * dequeue(Queue * q){
	Player * p;
	p = q->v[q->begin];
	q->begin = (q->begin + 1) % q->N;
	q->size --;
	return p;
}

void destroy_queue(Queue * q){
	free(q->v);
	free(q);
}
