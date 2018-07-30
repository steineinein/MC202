#include "hash.h"

/* função hash para calcular a posição a ser acessada no vetor*/
unsigned long hash (char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX;
}

Hash * criar_hash(){
	unsigned long i;
	Hash * tabela;
	tabela = malloc(sizeof(Hash));
	/* cria uma lista em cada posição da tabela */
	for (i = 0; i < MAX; i++)
		tabela->v[i] = criar_lista();
	return tabela;
}

void destruir_hash(Hash * tabela){
	unsigned long i;
	/* destroi a lista de cada posição */
	for (i = 0; i < MAX; i++)
		destruir_lista(tabela->v[i]);
	free(tabela);
}

void inserir(Hash * tabela, char * chave){
	unsigned long i;
	i = hash(chave);
	/* insere o elemento na posição dada pela função hash */
	tabela->v[i] = adicionar_elemento(tabela->v[i], chave);
}

/*void remover(Hash * tabela, char * chave){
	remover_elemento(tabela->v[hash(chave)], chave);
}*/

void imprimir_hash(Hash * tabela){
	unsigned long i;
	for (i = 0; i < MAX; i ++){
		imprimir_lista(tabela->v[i]);
	}
}

No * buscar(Hash * tabela, char * chave){
	No * item;
	/* verifica se o elemento existe na lisata na posição dada pelo hash*/
	item = buscar_elemento(tabela->v[hash(chave)], chave);
	return item;
}