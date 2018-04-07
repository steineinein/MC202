#include <stdlib.h>
#include "player.h"

typedef struct{
	Player **v;
	int begin, end, N, size;
} Queue;

Queue * create_queue(int N);

void queue(Queue* q, Player * p);

Player * dequeue(Queue* q);

void destroy_queue(queue* q);
