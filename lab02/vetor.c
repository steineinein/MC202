#include "vetor.h"
#include <string.h>
#include <stdlib.h>


p_vetor criar_vetor (int tam){
        p_vetor v;
        v = malloc(sizeof(Vetor));
        v->dados = malloc(tam * sizeof(Ordem));
        v->n = 0;
        v->alocado = tam;
        return v;
}

void destruir_vetor(p_vetor v){
	free(v->dados);
	free(v);
}

void ler_dados(Ordem *o, int i){
	int a;
	double b;
	o->identificador = i;
	scanf("%d", &a);
	o->quantidade = a;
	scanf("%lf ", &b);
	o->valor = b;
}

void adicionar_elemento (p_vetor v, Ordem o){
	int i;
	Ordem *temp;
	/* aloca mais espaço se necessario */
	if (v->n == v->alocado - 1){
		temp = v->dados;
		v->alocado *= 2;
		v->dados = malloc(v->alocado * sizeof(Ordem));
		for (i = 0; i < v->n; i++)
			v->dados[i] = temp[i];
		free(temp);
	}
	/* procura a posição que o elemento deve ser inserido */
	for (i = v->n - 1; i >= 0 && v->dados[i].valor > o.valor; i--){
		v->dados[i+1] = v->dados[i];
	}
	v->dados[i + 1] = o;
	v->n++;
}

void remover_elemento (p_vetor v, int i){
	Ordem *temp;
	for (; i < v->n; i++){
		v->dados[i] = v->dados[i+1];
	}
	(v->n)--;
	if (v->n <= v->alocado / 4){
		temp = v->dados;
		v->alocado /= 2;
		v->dados = malloc(v->alocado * sizeof(Ordem));
/*		memmove (v->dados, temp, v->n);*/
		for (i = 0; i < v->n; i++)
			v->dados[i] = temp[i];
		free(temp);
	}
}

int busca_binaria(p_vetor v, int l, int r, double x){
	int m;
	while (l <= r){
		m = l + (r-l)/2;
		if (v->dados[m].valor == x)
			return m;

		if (v->dados[m].valor < x)
			l = m + 1;

		else
			r = m - 1;
	}
	
	return -1;
}

int busca(p_vetor v, double x){
	int i;
	i = busca_binaria (v, 0, v->n, x);
	if (i == -1)
		return -1;
	while (v->dados[i].valor == x){
		i--;
	}
	return i + 1;
}

/*void adicionar_elemento (p_vetor v, Ordem o){
	int i;
	Ordem *temp;*/
	/* aloca mais espaço se necessario */
/*	if (v->n == v->alocado - 1){
		temp = v->dados;
		v->alocado *= 2;
		v->dados = malloc(v->alocado * sizeof(Ordem));
		for (i = 0; i < v->n; i++)
			v->dados[i] = temp[i];
		free(temp);
	}
*/	/* procura a posição que o elemento deve ser inserido */
	/*for (i = v->n - 1; i >= 0 && v->dados[i].valor > o.valor; i--){
		v->dados[i+1] = v->dados[i];
	}
	v->dados[i + 1] = o;
	v->n++;
}*/