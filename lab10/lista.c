#include "lista.h"

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

No * adicionar_elemento(No * lista, char * chave){
	No * novo;
	novo = malloc(sizeof(No));
	strcpy(novo->chave, chave);
	novo->prox = lista;
	return novo;
}

/*No * remover_elemento(No * list, char * chave);
*/
No * buscar_elemento(No * lista, char * chave){
	/* se a lista não for vazia, olha ela toda até encontra o elemento, se ele não exister 
	ou for vaiz retorna null, se não retorna o nó quer contém o elemento*/
	while(lista != NULL && strcmp(lista->chave, chave) != 0)
		lista = lista->prox;
	return lista;
}

void imprimir_lista(No * lista){
	while(lista != NULL){
		printf("%s\n", lista->chave);
		lista = lista->prox;
	}
}