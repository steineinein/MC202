#include "memoria.h"
#include <stdio.h>

int main(){
	p_mem memoria, aux;
	char operacao;
	int i, tam_total, n_operacao, tam1, tam2, end;

	scanf(" %d %d ", &n_operacao, &tam_total);

	memoria = cria_lista_vazia();
	/* cria um bloco de memória livre que começa no endereço zero 
	 * e do tamanho recebido */
	aux = cria_no (0, tam_total);
	/* adiciona esse bloco a lista de memória */
	adiciona_no(memoria, aux);
	/* repete de acordo com o numero de opeções recebidas */
	for(i = 0; i < n_operacao; i++){
		scanf("%c ", &operacao);
		switch (operacao){
			case 'A' :
				scanf(" %d\n", &tam1);
				aloca_memoria (memoria, tam1);
				break;
			case 'D' :
				scanf("%d %d\n", &end, &tam1);
				desaloca_memoria (memoria, end, tam1);
				break;
			case 'R' :
				scanf("%d %d %d\n", &end, &tam1, &tam2);
				realoca_memoria (memoria, end, tam1, tam2);
				break;
			case 'P' :
				printf("Segmentos livres da heap:\n");
				imprime_memoria(memoria);
				break;
		}
	}
	/* desaloca a memoria referente aos mallocs */
	destroi_lista(memoria);
	return 0;
}