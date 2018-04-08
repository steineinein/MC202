#include "fila.h"
#include <math.h>
#include <stdio.h>

/* realiza todas as n_match partidas do roung atual da upper bracket */
int ub_round(Queue * ub_q, Queue * lb_q, int * match_id, int n_match, int k);

/* imprime o resultado da partida da upper bracket na tela */
void print_ub_match(Player* winner, Player* loser, int match_id);

/* realiza todas as n_match partidas do roung atual da lower bracket */
int lb_round(Queue * lb_q, int * match_id, int n_match, int k);

/* imprime o resultado da partida da lower bracket na tela */
void print_lb_match(Player* winner, Player* loser, int match_id);

/* recebe as duas filas com um jogador cada e realiza a partida final*/
int grand_final(Queue * ub_q, Queue * lb_q);

/* recebe o vencedor e o perdedor da final e imprime o resultado na tela*/
void print_grand_final(Player * winner, Player * loser);

/* realiza a partida entre dois jogadores, determinando o vencedor e o ganhador*/
void do_battle(Player * p1, Player * p2, Player ** winner, Player ** loser);

int main(){
	int N, K, H, i, champ_flag, tamanho;
	int lb_match_id, ub_match_id, lb_n_match, ub_n_match;
	Queue * ub_q, * lb_q;
	/* escaneia o N que define o número de jogadores e K que define o quanto de habilidade os 
	jogadores recuperam no descaço */
	scanf("%d %d", &N, &K);
	/* define o número de jogadores 2^N */
	tamanho = pow(2, N);
	/* cria a fila da upper bracket que comporta 2^N jogadores */
	ub_q = create_queue(tamanho);
	/* cria a fila da lower bracket que comporta metade dos jogadores da upper bracket */
	lb_q = create_queue(tamanho/2);

	/* repete enquanto tiver jogador para incializar*/
	for (i = 0; i < tamanho; i++){
		scanf("%d", &H);
		/* incializa o jogador e enfilera ele, identificando os jogadores a partir do número 1
		e atribuindo o valor H a suas habilidades atuais e máximas*/
		queue(ub_q, start_player(i + 1, H));
	}
	/* inicializa a flag que determina quando o campeão foi escolhido */
	champ_flag = 0;
	/* numero de partidas a ser jogadas no round atual na upper bracket e na 
	lower bracket */
	ub_n_match = tamanho/2;
	lb_n_match = tamanho/4;
	/* inicializa a numeração das partidas para a lower e upper bracket*/
	ub_match_id = 1;
	lb_match_id = 1;
	/* repete enquanto um campeão não for escolhido */
	while(champ_flag == 0){
		/* se há partidas na upper bracker serem jogadas nesse round, então ela é jogada*/
		if(ub_n_match > 0){
			/* joga-se a upper bracker e atualiza o número de partidas da rodada seguinte */
			ub_n_match = ub_round(ub_q, lb_q, &ub_match_id, ub_n_match, K);
			/* atualiza o número de partidas a serem jogadas na lower bracker*/
			lb_n_match = lb_q->size/2;
		}
		/* se há partidas na lower bracker serem jogadas nesse round, então ela é jogada*/
		if(lb_n_match > 0)
			/* joga-se a lower bracker e atualiza o número de partidas da rodada seguinte */
			lb_n_match = lb_round(lb_q, &lb_match_id, lb_n_match, K);
		/* se não a mais partidas a serem jogadas em ambas as brackets, então há apenas um
		jogador em cada e é jogada a final*/
		if(ub_n_match == 0 && lb_n_match == 0)
			champ_flag = grand_final(ub_q, lb_q);
	}
	return 0;
}

/* realiza todas as n_match partidas do roung atual da upper bracket */
int ub_round(Queue * ub_q, Queue * lb_q, int * match_id, int n_match, int k){
	int i;
	Player * p1, * p2, * winner, * loser;

	for (i = 0; i < n_match; i++){
		/* desenfilera os dois jogadores que vão jogar a próxima partida */
		p1 = dequeue(ub_q);
		p2 = dequeue(ub_q);
		/* joga-se a partida e define os vencedores */
		do_battle(p1, p2, &winner, &loser);
		/* modifica a habilidade atual dos jogadores de acordo com as regras */
		modify_player(winner, winner->h_current - loser->h_current + k);
		modify_player(loser, (loser->h_current / 2) + k);
		/* imprime o resultado */
		print_ub_match(winner, loser, *match_id);
		/* o vencedor continua na upper bracket, logo é enfilerado nela */
		queue(ub_q, winner);
		/* o perdedor vai para a lower bracket, logo é enfilerado nela */
		queue(lb_q, loser);
		/* avança para a próxima partida */
		(*match_id)++;
	}
	/* retorna o número de partidas a ser jogada na próxima rodada */
	return (ub_q->size/2);
}

/* imprime o resultado da partida da upper bracket na tela */
void print_ub_match(Player* winner, Player* loser, int match_id){
	if (winner->id < loser->id)
		printf("Partida %d: %d vs %d venceu %d\n",match_id, winner->id, loser->id, winner->id);
	else
		printf("Partida %d: %d vs %d venceu %d\n",match_id, loser->id, winner->id, winner->id);
}

/* realiza todas as n_match partidas do roung atual da lower bracket */
int lb_round(Queue * lb_q, int * match_id, int n_match, int k){
	int i;
	Player * p1, * p2, * winner, * loser;

	for (i = 0; i < n_match; i++){
		/* desenfilera os dois jogadores que vão jogar a próxima partida */
		p1 = dequeue(lb_q);
		p2 = dequeue(lb_q);
		/* joga-se a partida e define os vencedores */
		do_battle(p1, p2, &winner, &loser);
		/* modifica a habilidade atual dos jogadores de acordo com as regras */
		modify_player(winner, winner->h_current - loser->h_current + k);
		/* imprime o resultado */
		print_lb_match(winner, loser, *match_id);
		/* o vencedor continua na lower bracket, logo é enfilerado nela */
		queue(lb_q, winner);
		/* o perdedor é eliminado do torneio */
		delete_player(loser);
		/* avança para a próxima partida */
		(*match_id)++;
	}
	/* retorna o número de partidas a ser jogada na próxima rodada */
	return (lb_q->size/2);
}

/* imprime o resultado da partida da lower bracket na tela */
void print_lb_match(Player* winner, Player* loser, int match_id){
	if (winner->id < loser->id)
		printf("Partida %d da repescagem: %d vs %d venceu %d\n",match_id, winner->id, loser->id, winner->id);
	else
		printf("Partida %d da repescagem: %d vs %d venceu %d\n",match_id, loser->id, winner->id, winner->id);
}

/* recebe as duas filas com um jogador cada e realiza a partida final*/
int grand_final(Queue * ub_q, Queue * lb_q){
	Player * p1, * p2, * winner, * loser;
	/* retira os útlimo jogadors de cada fila */
	p1 = dequeue(ub_q);
	p2 = dequeue(lb_q);
	/* na grande final os participantes jogam com suas habilidades no máximo */
	p1->h_current = p1->h_max;
	p2->h_current = p2->h_max;
	/* realiza a batalha */
	do_battle(p1, p2, &winner, &loser);
	/* imprime o resultado */
	print_grand_final(winner, loser);
	/* libera os jogadores */
	free(p1);
	free(p2);
	/* destroi as filas agora que estão vazias */
	destroy_queue(ub_q);
	destroy_queue(lb_q);
	/* retorna 1 para indicar que a grande final ocorreu */
	return 1;
}

/* recebe o vencedor e o perdedor da final e imprime o resultado na tela*/
void print_grand_final(Player * winner, Player * loser){
	if (winner->id < loser->id)
		printf("Final do torneio: %d vs %d campeao %d\n", winner->id, loser->id, winner->id);
	else
		printf("Final do torneio: %d vs %d campeao %d\n", loser->id, winner->id, winner->id);
}

/* realiza a partida entre dois jogadores, determinando o vencedor e o ganhador*/
void do_battle(Player * p1, Player * p2, Player ** winner, Player ** loser){
	/* o jogador com maior habilidade vence */
	if(p1->h_current > p2->h_current){
		*winner = p1;
		*loser = p2;
	}
	else if(p2->h_current > p1->h_current){
		*winner = p2;
		*loser = p1;
	}
	/* se as habilidade forem iguais o jogador com o menor indice vence*/
	else if(p1->id < p2->id){
		*winner = p1;
		*loser = p2;
	}
	else{
		*winner = p2;
		*loser = p1;
	}
}