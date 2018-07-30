/* Nesse projeto serão considerados vertices cada posição no mapa e serão consideradas
aresta a posições vizinhas na qual o drone consegue trafegar (altura que o drone consegue
voar é maior que a altura do monólito) */
#include <stdio.h>
#include "graph.h"
#include "lista.h"
#include <limits.h>

typedef struct{
	int x, y;
} coord;

/* mapeia a relação entre as arrestas e os vertices, ou seja se o drone consegue sair 
de uma posição e ir para a vizinha */
void mapeia_terreno(Graph * g, int * mapa_altura, int h_drone, int m);

/* dada as coordenadas (x,y) converte elas a sua posição referente no vetor*/
int pos(int x, int y, int n_col);

int pos_y(int pos, int n_col);

int pos_x(int pos, int n_col);

int dir(int i);
int esq(int i);
int acima(int i, int m);
int abaixo(int i, int m);

/* pega o caminho entre a posição final e a posição inicial e coloca esse caminho no mapa
onde o drone não passa é posto '#' e onde ele passa é posto um inteiro positivo que representa
quantos movimentos foram feitos para chegar na quela posição */
int * mapeia_caminho(int * pai, int dest, int tam);

int caminho_recursivo(int * mapa, int * pai,int dest, int cont);

void imprime_caminho(int * mapa_caminho, int tam, int m);

int main(){
	int i, h_drone, n_linha, n_col, n_pos;
	int * mapa_altura, * pai, * mapa_caminho;
	coord ini, base;
	Graph * g;

	scanf("%d %d %d",&h_drone, &ini.x, &ini.y);
	scanf("%d %d %d %d", &base.x, &base.y, &n_linha, &n_col);

	/*invés de trabalhar com uma matrix nxm usamos uma (n+2)x(m+2) para evitar problemas
	com fronteiras*/
	ini.x++;
	ini.y++;
	base.x++;
	base.y++;
	n_linha = n_linha + 2;
	n_col = n_col + 2;
	n_pos = (n_linha)*(n_col);
	mapa_altura = malloc(n_pos * sizeof(int));
	/* todas a posições são inicializadas com um valor maximo para o drone não passar por lá*/
	for(i = 0; i < n_pos; i++)
		mapa_altura[i] = INT_MAX;
	/* escreve uma matriz menor dentro da matriz maior 
	temos:	$ $ $ $ $ invés de: 1 6 7
			$ 1 6 7 $			2 5 0
			$ 2 5 0 $			3 1 0
			$ 3 1 0 $
			$ $ $ $ $*/
	for (i = n_col+1; i < n_pos-(n_col+1); i = i+1){
		scanf("%d ", &mapa_altura[i]);
		if (i % n_col == n_col - 2)
			i = i + 2;
	}
	g = create_graph(n_pos);
	/* mapeia o terreno, ou seja cria aresta onde o drone consegue travessar */
	mapeia_terreno(g, mapa_altura, h_drone, n_col);
	/* cria a arvóre de caminhos dada uma raiz, nesse caso a posição incial do drone*/
	pai = paths(g, pos(ini.x, ini.y, n_col));
	/* pega a arvóre que é o vetor pai e escreve o caminho entre a posição inicial do
	drone e a base de operações */
	mapa_caminho = mapeia_caminho(pai, pos(base.x, base.y, n_col), n_pos);

	imprime_caminho(mapa_caminho, n_pos, n_col);

	free(mapa_caminho);
	free(mapa_altura);
	destroy_graph(g);
	free(pai);

	return 0;
}

void mapeia_terreno(Graph * g, int * mapa_altura, int h_drone, int m){
	int pos_atual, pos_aux;
	/* mapeia apenas o mapa normal, não passando pelas linhas e colunas extras */
	for (pos_atual = m+1; pos_atual < g->n - (m+1); pos_atual ++){
		/* se o drone não consegue voar na posição atual, não precisamos olhar sua
		relação com os vizinho*/
		if (mapa_altura[pos_atual] <= h_drone){
			/* se ele consegue voar então olhamos, se  ele consegue voar da posição atual
			para os seu vizinho, se consegue inserimos uma arresta no grafo. */
			pos_aux = dir(pos_atual);
			if (mapa_altura[pos_aux] <= h_drone)
				insert_edge(g, pos_aux, pos_atual);
			pos_aux = esq(pos_atual);
			if (mapa_altura[pos_aux] <= h_drone)
				insert_edge(g, pos_aux, pos_atual);
			pos_aux = acima(pos_atual, m);
			if (mapa_altura[pos_aux] <= h_drone)
				insert_edge(g, pos_aux, pos_atual);
			pos_aux = abaixo(pos_atual, m);
			if (mapa_altura[pos_aux] <= h_drone)
				insert_edge(g, pos_aux, pos_atual);
		}
		if (pos_atual % m == m - 2)
			pos_atual = pos_atual + 2;
	}
}

int * mapeia_caminho(int * pai, int dest, int tam){
	int * mapa = malloc(tam * sizeof(int));
	int i;
	/* inicializa o mapa com -1, -1 significa que o drone não vou nessa posição */
	for (i = 0; i < tam; i++)
		mapa[i] = -1;
	/* chama a função para escrever o caminho no mapa recursivamente
	onde pai é a posição inicial e des o destino do drone, 0 é o número de movimentos
	já realizados pelo drone */
	caminho_recursivo(mapa, pai, dest, 0);
	return mapa;
}

int caminho_recursivo(int * mapa, int * pai,int dest, int cont){
	/* condição incial, é de onde o drone começa, escreve o número inicial
	de movimento dos drones */
	if (pai[dest] == dest){
		mapa[dest] = cont;
		return ++cont;
	}
	/* escreve o número de movimentos necessário para chegar até a posição atual*/
	else{
		cont = caminho_recursivo(mapa, pai, pai[dest], cont);
		mapa[dest] = cont;
		return ++ cont;
	}
}

void imprime_caminho(int * mapa_caminho, int tam, int m){
	int i;
	for (i = m+1; i < tam -(m+1); i++){
		if (mapa_caminho[i] == -1)
			printf("#");
		else 
			printf("%d", mapa_caminho[i]);
		if (i % m == m-2){
			printf("\n");
			i = i + 2;
		}
		else
			printf(" ");
	}
}


int pos(int x, int y, int n_col){
	int pos;
	pos = y*n_col + x;
	return pos;
}

int pos_y(int pos, int n_col){
	return pos/n_col;
}

int pos_x(int pos, int n_col){
	return pos - (pos / n_col) * n_col;
}

int dir(int i){
	return i + 1;
}
int esq(int i){
	return i - 1;
}
int acima(int i, int m){
	return i - m;
}
int abaixo(int i, int m){
	return i + m;
}