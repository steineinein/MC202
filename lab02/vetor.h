#include <stdio.h>
#include "ordem.h"

typedef struct {
	Ordem *dados;
	int n;
	int alocado;
}	Vetor;

typedef Vetor * p_vetor;

p_vetor criar_vetor (int tam);

void destruir_vetor(p_vetor v);

void ler_dados(Ordem *o, int i);

void adicionar_elemento (p_vetor, Ordem o);

void remover_elemento (p_vetor, int i);

int busca(p_vetor v, double x);