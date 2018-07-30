#include "graph.h"

No * criar_lista(){
	return NULL;
}

void destruir_lista(No * lista){
    No * aux;
    /* equanto ela não for vaiza deleta cada nó*/
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

No * insere_na_lista(No * lista, int v, int peso){
	No * novo;
	novo = malloc(sizeof(No));
	novo->v = v;
	novo->peso = peso;
	novo->prox = lista;
	return novo;
}

No * remove_da_lista(No * lista, int v){
	No * proximo;
	if (lista == NULL)
		return NULL;
	else if (lista->v == v){
		proximo = lista->prox;
		free (lista);
		return proximo;
	}
	else{
		lista->prox = remove_da_lista(lista->prox, v);
		return lista;
	}
}

void imprimir_lista(No* lista){
	while (lista != NULL){
		printf("%d ", lista->v);
		lista = lista->prox;
	}
}

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
void insert_edge(Graph * g, int u, int v, int peso){
	g->adjacent[u] = insere_na_lista(g->adjacent[u], v, peso);
	g->adjacent[v] = insere_na_lista(g->adjacent[v], u, peso);
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

pai_dijkstra * dijkstra(Graph * g, int s){
	int v;
	pai_dijkstra * pai;
	No * t;
	FilaPrio * h;
	pai = malloc(sizeof(pai_dijkstra) * g->n);
	h = criar_fila_prio(g->n);
	for (v = 0; v < g->n; v++){
		pai[v].v = -1;
		pai[v].dist = -1;
		inserir(h, v, INT_MAX);
	}
	/* o ponto inicil é pai dele mesmo, e distancia até éle mesmo é zero */
	pai[s].v = s;
	pai[s].dist = 0;
	/* caminho menor tem maior prioridade */
	diminuir_prioridade(h, s, 0);
	while(!eh_vazia(h)){
		/* procura o vertice mais proximo */
		v = extrair_minimo(h);
		/* se for INT_MAX não existe caminho*/
		if(prioridade(h, v) != INT_MAX){
			/* olha todos os vizinhos */
			for(t = g->adjacent[v]; t != NULL; t = t->prox){
				/* se o caminho for menos do que se conhece o atualiza */
				if (prioridade(h,v) + t->peso < prioridade(h, t->v)){
					diminuir_prioridade(h, t->v, prioridade(h,v) + t->peso);
					/* guarda quem é o pai dele e sua distancia até o ponto inicial */
					pai[t->v].v = v;
					pai[t->v].dist = prioridade(h, t->v);
				}
			}
		}
	}
	destruir_fila_prio(h);
	return pai;
}