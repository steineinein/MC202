#ifndef PARTICIPANTE_H
#define PARTICIPANTE_H
#include <stdlib.h>
#endif

/* estrutura de um jogador, contendo respectivamente: um numero identificador,
sua habilidade atual e sua habilidade máxima */
typedef struct{
	int id, h_current, h_max;
} Player;

/* inicia um jogador com identificador id e com habilidade atual e máxima h*/
Player * start_player(int id, int h);

/* modifica a habilidade atual de um jogado para h */
void modify_player(Player * p, int h);

/* deleta o jogador p*/
void delete_player(Player * p);
