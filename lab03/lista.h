#include <stdlib.h>

typedef struct no_mem{
    int end_ini, tamanho;
    struct no_mem * prox;
} No_mem;

typedef No_mem * p_mem;

/* cria lista vazia com um nó dummy
 * atribuindo valores -1 (impossiveis) para os dados */
p_mem cria_lista_vazia();

/* destroi a lista */
void destroi_lista(p_mem lista);

/* cria e retorna um novo nó com os dados indicados */
p_mem cria_no (int end, int tam);

/* adiciona um nó a uma lista existente */
void adiciona_no(p_mem anterior, p_mem novo);

/* remove um nó de uma lista existente*/
void remove_no(p_mem anterior, p_mem atual);

/* busca um nó com endereço inicial maior ou igual ao buscado
 * devolve o nó anterior */
p_mem busca_end_maior(p_mem lista, int end);

/* busca um nó com tamanho maior ou igual ao necessário
 * devolve o nó anterior */
p_mem busca_tam_maior_igual(p_mem lista, int tam);

