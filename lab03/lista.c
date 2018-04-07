#include "lista.h"

/* cria lista vazia com um nó dummy
 * atribuindo valores -1 (impossiveis) para os dados */
p_mem cria_lista_vazia(){
    p_mem dummy;
    dummy = malloc(sizeof(No_mem));
    dummy->end_ini = -1;
    dummy->tamanho = -1;
    dummy->prox = NULL;
    return dummy;
}

/* destroi a lista */
void destroi_lista(p_mem lista){
    p_mem aux;
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

/* cria e retorna um novo nó com os dados indicados */
p_mem cria_no (int end, int tam){
    p_mem novo;
    novo = malloc(sizeof(No_mem));
    novo->end_ini = end;
    novo->tamanho = tam;
    novo->prox = NULL;
    return novo;        
} 

/* adiciona um nó a uma lista existente */
void adiciona_no(p_mem anterior, p_mem novo){
    novo->prox = anterior->prox;
    anterior->prox = novo;
}

/* remove um nó de uma lista existente*/
void remove_no(p_mem anterior, p_mem atual){
    anterior->prox = atual->prox;
    free(atual);
}

/* busca um nó com endereço inicial maior ou igual ao buscado
 * devolve o nó anterior */
p_mem busca_end_maior(p_mem lista, int end){
    while (lista->prox != NULL){
        if (lista->prox->end_ini > end)
            return lista;
        lista = lista->prox;
    }
    return lista;
}

/* busca um nó com tamanho maior ou igual ao necessário
 * devolve o nó anterior */
p_mem busca_tam_maior_igual(p_mem lista, int tam){
    while (lista->prox->tamanho < tam && lista->prox != NULL){
        lista = lista->prox;
    }
    return lista;
}
