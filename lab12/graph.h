#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fila_prio.h"

typedef struct no{
    int v;
    int peso;
    struct no * prox;
} No;

typedef struct{
	No ** adjacent;
	int n;
} Graph;

/* vertice e sua distancia ao ponto inicial */
typedef struct{
	int v, dist;
}pai_dijkstra;

/* cria um grafo com n arrestas*/
Graph * create_graph(int n);

/* destroi o grafo g*/
void destroy_graph(Graph * g);

/* insere a aresta de u e v */
void insert_edge(Graph * g, int u, int v, int peso);

/* remove a aresta de u e v */
void remove_edge(Graph * g, int u, int v);

/* cria um arvore que conecta todos os elementos do grafo a raiz
   devolver um vetor que contem o pai de cada elemento na arvore*/
int * paths(Graph * g, int s);

/* imprime as relações */
void print_graph(Graph * g);

/* recebe um grafo e o ponto de partida s, determina todos oe menoras caminho de s
devolver o vetor pai_dijkstra que contém os filhos de s e a sua distancia até s*/
pai_dijkstra * dijkstra(Graph * g, int s);

#endif