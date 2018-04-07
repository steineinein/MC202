#include "participante.h"

Player * start_player(int i, int h){
	player * p = malloc(sizeof(Player));
	p->i = i;
	p->h_current = h;
	p->h_max = h;
	return p;	
}

Player * modify_player(Player * p, int h){
	if (h > p->h_max)
		p->h_current = p->h_max;
	else if(h < 0)
		p->h_current = 0;
	else
		p->h_current = h;
	return p;
}

void delete_player(Player * p){
	free (p);
}
