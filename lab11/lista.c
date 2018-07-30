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

No * insere_na_lista(No * lista, int v){
	No * novo;
	novo = malloc(sizeof(No));
	novo->v = v;
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