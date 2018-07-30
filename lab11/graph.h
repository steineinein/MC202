#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include "lista.h"

typedef struct{
	No ** adjacent;
	int n;
} Graph;

/* cria um grafo com n arrestas*/
Graph * create_graph(int n);

/* destroi o grafo g*/
void destroy_graph(Graph * g);

/* insere a aresta de u e v */
void insert_edge(Graph * g, int u, int v);

/* remove a aresta de u e v */
void remove_edge(Graph * g, int u, int v);

/* cria um arvore que conecta todos os elementos do grafo a raiz
   devolver um vetor que contem o pai de cada elemento na arvore*/
int * paths(Graph * g, int s);

/* imprime as relações */
void print_graph(Graph * g);

#endif