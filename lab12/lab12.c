#include "graph.h"
#define VEL 20 /* m/s */
#define TEMPO_DESARMAR_BOMBA 600 /* s */
#define TEMPO_DESATIVAR_GAS 120 /* s */
#define UMA_HORA 3600 /* s */

/* distancia entre um predio e outro*/
typedef struct{
	int p1, p2, dist;
}predios;

/* calculca o para percorrer a distancia s1 + s2*/
int calc_tempo(int s1, int s2);

void imprime_caminho(pai_dijkstra * pai, int dest);

int main(){
	int i, n_vertices, n_arestas, tam_teia, pos_amigao, pos_bomba, pos_mj, t1, t2;
	predios * cidade;
	Graph * g;
	pai_dijkstra * pai1, * pai2, *pai3;

	scanf("%d %d ", &n_vertices, &n_arestas);
	cidade = malloc(n_arestas * sizeof(predios));
	for(i = 0; i < n_arestas; i++){
		scanf("%d %d %d ", &cidade[i].p1, &cidade[i].p2, &cidade[i].dist);
	}
	scanf("%d %d %d %d", &tam_teia, &pos_amigao, &pos_bomba, &pos_mj);
	g =  create_graph(n_vertices);
	/* cria as aresta, as aressa são somente os predios o amigão consegue travessar, distancia entre os prediso é menor que o tamanho da teia*/
	for(i = 0; i < n_arestas; i++){
		if(cidade[i].dist <= 2* tam_teia){
			insert_edge(g, cidade[i].p1, cidade[i].p2, cidade[i].dist);
		}
	}

	/* verifica os menores caminhos com 3 bases diferentes */
	pai1 = dijkstra(g, pos_amigao);
	pai2 = dijkstra(g, pos_bomba);
	pai3 = dijkstra(g, pos_mj);
	/* existem 2 menores caminhos possiveis, ou indo para mj primeirou ou indo para bomba primeiro
	calcula o tempo de cada opção */
	t1 = calc_tempo(pai1[pos_bomba].dist, pai2[pos_mj].dist) + TEMPO_DESARMAR_BOMBA + TEMPO_DESATIVAR_GAS;
	t2 = calc_tempo(pai1[pos_mj].dist, pai3[pos_bomba].dist) + TEMPO_DESARMAR_BOMBA + TEMPO_DESATIVAR_GAS;
	/* escolhe a opção mais rápido dentro do tempo limite de uma hora */
	if (t1 <= t2 && t1 < UMA_HORA){
		imprime_caminho(pai1, pai1[pos_bomba].v);
		imprime_caminho(pai2, pai2[pos_mj].v);
		printf("%d\n", pos_mj);
	}
	else if(t1 > t2 && t2 < UMA_HORA){
		imprime_caminho(pai1, pai1[pos_mj].v);
		imprime_caminho(pai3, pai3[pos_bomba].v);
		printf("%d\n", pos_bomba);
	}
	/* caso nenhuma seja fazível em uma hora escolhe a que gastaria menos tempo, desarmar a bomba ou salvar mj*/
	else{
		t1 = calc_tempo(pai1[pos_bomba].dist, 0) + TEMPO_DESARMAR_BOMBA;
		t2 = calc_tempo(pai1[pos_mj].dist, 0) + TEMPO_DESATIVAR_GAS;
		if(t1 < t2){
			imprime_caminho(pai1, pai1[pos_bomba].v);
			printf("%d\n", pos_bomba);
		}
		else{
			imprime_caminho(pai1, pai1[pos_mj].v);
			printf("%d\n", pos_mj);
		}
	}

	free(pai1);
	free(pai2);
	free(pai3);
	free(cidade);
	destroy_graph(g);
	return 0;
}

/* distancia divida pela velocidade */
int calc_tempo(int s1, int s2){
	return s1/VEL + s2/VEL;
}

void imprime_caminho(pai_dijkstra * pai, int dest){
	if (pai[dest].v != dest)
		imprime_caminho(pai, pai[dest].v);
	printf("%d ", dest);
}