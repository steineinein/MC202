#include "vetor.h"

void executa_venda(p_vetor buy, p_vetor sell);


int main(){
	int i;
	char tipo;
	Ordem ordem;
	p_vetor buy, sell;

	i = 0;
	buy = criar_vetor(10);
	sell = criar_vetor(10);
	while ((tipo = getchar()) != '#'){
		ler_dados(&ordem, i + 1);
		switch (tipo){
			case 'C':
				adicionar_elemento (buy, ordem);
				break;
			case 'V':
				adicionar_elemento (sell, ordem);
				break;
		}
		i++;
		executa_venda(buy, sell);
	}
	return 0;
}


void executa_venda(p_vetor buy, p_vetor sell){
	int i, pos;
	for (i = 0; i < buy->n; i++){
		pos = busca(sell, buy->dados[i].valor);
		if (pos != - 1){
			while (buy->dados[i].quantidade > 0 && buy->dados[i].valor == sell->dados[pos].valor){
				if (buy->dados[i].quantidade < sell->dados[pos].quantidade){
					printf("ordem %d vende para ordem %d a quantidade %d por %.2f\n", sell->dados[pos].identificador, buy->dados[i].identificador, buy->dados[i].quantidade, buy->dados[i].valor);
					printf("ordem %d concluida\n", buy->dados[i].identificador);
					sell->dados[pos].quantidade = sell->dados[pos].quantidade - buy->dados[i].quantidade;
					buy->dados[i].quantidade = 0;
				}
				else if (buy->dados[i].quantidade == sell->dados[pos].quantidade){
					printf("ordem %d vende para ordem %d a quantidade %d por %.2f\n", sell->dados[pos].identificador, buy->dados[i].identificador, buy->dados[i].quantidade, buy->dados[i].valor);
					if (buy->dados[i].identificador > sell->dados[pos].identificador){
						printf("ordem %d concluida\n", sell->dados[pos].identificador);
						printf("ordem %d concluida\n", buy->dados[i].identificador);
					}
					else{
						printf("ordem %d concluida\n", buy->dados[i].identificador);
						printf("ordem %d concluida\n", sell->dados[pos].identificador);
					}
					remover_elemento (sell, pos);
					buy->dados[i].quantidade = 0;
				}
				else{
					printf("ordem %d vende para ordem %d a quantidade %d por %.2f\n", sell->dados[pos].identificador, buy->dados[i].identificador, sell->dados[pos].quantidade, buy->dados[i].valor);
					printf("ordem %d concluida\n", sell->dados[pos].identificador);
					buy->dados[i].quantidade = buy->dados[i].quantidade - sell->dados[pos].quantidade;
					remover_elemento (sell, pos);
				}
			}
			if (buy->dados[i].quantidade == 0){
				remover_elemento (buy, i);
				i--;
			}
		}
	}
}