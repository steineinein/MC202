#include "graph.h"

void busca_em_profundidade(Graph * g, int * pai, int p, int v);
/* cria um grafo com n arrestas*/
Graph * create_graph(int n){
	int i;
	Graph * g = malloc(sizeof(Graph));
	g->n = n;
	g->adjacent = malloc(n * sizeof(No *));
	for (i = 0; i < n; i++)
		g->adjacent[i] = criar_lista();
	return g;
}

/* destroi o grafo g*/
void destroy_graph(Graph * g){
	int i;
	for (i = 0; i < g->n; i++)
		destruir_lista(g->adjacent[i]);
	free(g->adjacent);
	free(g);
}

/* insere a aresta de u e v */
void insert_edge(Graph * g, int u, int v){
	g->adjacent[u] = insere_na_lista(g->adjacent[u], v);
	g->adjacent[v] = insere_na_lista(g->adjacent[v], u);
}

/* remove a aresta de u e v */
void remove_edge(Graph * g, int u, int v){
	g->adjacent[u] = remove_da_lista(g->adjacent[u], v);
	g->adjacent[v] = remove_da_lista(g->adjacent[v], u);
}

/* cria um arvore que conecta todos os elementos do grafo a raiz
   devolver um vetor que contem o pai de cada elemento na arvore*/
int * paths(Graph * g, int s){
	int i, *pai = malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)
		pai[i] = -1;
	busca_em_profundidade(g, pai, s, s);
	return pai;
}


void busca_em_profundidade(Graph * g, int * pai, int p, int v){
	No * t;
	pai[v] = p;
	for (t = g->adjacent[v]; t!= NULL; t = t->prox){
		if (pai[t->v] == -1)
			busca_em_profundidade(g, pai, v, t->v);
	}
}

void print_graph(Graph * g){
	int i;
	for(i = 0; i < g->n; i++){
		printf("%d: ", i);
		imprimir_lista(g->adjacent[i]);
		printf("\n");
	}
}