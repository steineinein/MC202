#include "participante.h"

/* inicia um jogador com identificador id e com habilidade atual e máxima h*/
Player * start_player(int id, int h){
	Player * p = malloc(sizeof(Player));
	p->id = id;
	p->h_current = h;
	p->h_max = h;
	return p;	
}

/* inicia um jogador com identificador id e com habilidade atual e máxima h*/
void modify_player(Player * p, int h){
	/* habilitade atual não pode ser maior que a máxima dele*/
	if (h > p->h_max)
		p->h_current = p->h_max;
	/* não pode ter habilidade negativa */
	else if(h < 0)
		p->h_current = 0;
	else
		p->h_current = h;
}

/* deleta o jogador p*/
void delete_player(Player * p){
	free (p);
}
