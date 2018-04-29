#include "fila_prioridade.h"
#include <stdio.h>

void sobe_no_heap(FP * fprio, int k);
void desce_no_heap(FP * fprio, int k);
void troca(Item * item_a, Item * item_b);
int pai(int i);
int f_esq(int i);
int f_dir(int i);

FP * criar_filaprio(int tam, fcmp cmp){
	FP * fprio = malloc (sizeof(FP));
	fprio->v = malloc(tam * sizeof(Item));
	fprio->n = 0;
	fprio->tamanho = tam;
	fprio->cmp = cmp;
	return fprio;
}
void destroir_filaprio(FP* fprio){
	free(fprio->v);
	free(fprio);
}

void inserir(FP * fprio, Item item){
	fprio->v[fprio->n] = item;
	fprio->n++;
	sobe_no_heap(fprio, fprio->n - 1);
}

Item extrair_maximo(FP * fprio){
	Item item = fprio->v[0];
	troca(&fprio->v[0], &fprio->v[fprio->n -1]);
	fprio->n--;
	desce_no_heap(fprio, 0);
	return item;
}

void sobe_no_heap(FP * fprio, int k){
	if (k > 0 && fprio->cmp(fprio->v[pai(k)],fprio->v[k]) < 0){
		troca(&fprio->v[k], &fprio->v[pai(k)]);
		sobe_no_heap(fprio, pai(k));
	}
}

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

void troca(Item * item_a, Item * item_b){
	Item temp = *item_a;
	*item_a = *item_b;
	*item_b = temp;
}

int pai(int i){
	return ((i - 1)/2);
}
int f_esq(int i){
	return (2*i + 1);
}
int f_dir(int i){
	return (2*i + 2);
}

int vazia (FP * fprio){
	if (fprio->n == 0)
		return 1;
	return 0;
}
int cheia (FP * fprio){
	if (fprio->n == fprio->tamanho)
		return 1;
	return 0;
}