/* TAD de uma fila de prioridade em max heap*/

#include "fila_prioridade.h"
#include <stdio.h>

void sobe_no_heap(FP * fprio, int k);
void desce_no_heap(FP * fprio, int k);
void troca(Item * item_a, Item * item_b);
int pai(int i);
int f_esq(int i);
int f_dir(int i);

/* cria uma fila de prioridade de tamanho tam com função de comparação que
 * for definida no cliente*/
FP * criar_filaprio(int tam, fcmp cmp){
	FP * fprio = malloc (sizeof(FP));
	fprio->v = malloc(tam * sizeof(Item));
	fprio->n = 0;
	fprio->tamanho = tam;
	fprio->cmp = cmp;
	return fprio;
}
/* destroi a fila recebida*/
void destroir_filaprio(FP* fprio){
	free(fprio->v);
	free(fprio);
}
/* insere um item na fila de prioridades */
void inserir(FP * fprio, Item item){
	fprio->v[fprio->n] = item;
	fprio->n++;
	sobe_no_heap(fprio, fprio->n - 1);
}
/* extrai o item com maior prioridade */
Item extrair_maximo(FP * fprio){
	Item item = fprio->v[0];
	troca(&fprio->v[0], &fprio->v[fprio->n -1]);
	fprio->n--;
	desce_no_heap(fprio, 0);
	return item;
}
/* olha o pai do elemento k, se o elemento k for maior que o pai, troca e repete isso até
não ser maior*/
void sobe_no_heap(FP * fprio, int k){
	if (k > 0 && fprio->cmp(fprio->v[pai(k)],fprio->v[k]) < 0){
		troca(&fprio->v[k], &fprio->v[pai(k)]);
		sobe_no_heap(fprio, pai(k));
	}
}
/* olha o filho do elemento k, se o elemento k for menor que o filha, troca e repete isso até
não ser menor*/
void desce_no_heap(FP* fprio, int k){
	int maior_filho;
	if (f_esq(k) < fprio->n){
		maior_filho = f_esq(k);
		if (f_dir(k) < fprio->n && fprio->cmp(fprio->v[f_esq(k)],fprio->v[f_dir(k)]) < 0)
			maior_filho = f_dir(k);
		if (fprio->cmp(fprio->v[k],fprio->v[maior_filho]) < 0){
			troca (& fprio->v[k], & fprio->v[maior_filho]);
			desce_no_heap (fprio, maior_filho);
		}
	}
}
/* troca dois elementos de posição*/
void troca(Item * item_a, Item * item_b){
	Item temp = *item_a;
	*item_a = *item_b;
	*item_b = temp;
}
/* calcula o pai do elemento i*/
int pai(int i){
	return ((i - 1)/2);
}
/* calcula o filho esquerdo do elemento i*/
int f_esq(int i){
	return (2*i + 1);
}
/* calcula o filho direito do elemento i*/
int f_dir(int i){
	return (2*i + 2);
}
/* retorna 1 se vazia e 0 se não */
int vazia (FP * fprio){
	if (fprio->n == 0)
		return 1;
	return 0;
}
/* retorna 1 se cheia e 0 se não */
int cheia (FP * fprio){
	if (fprio->n == fprio->tamanho)
		return 1;
	return 0;
}