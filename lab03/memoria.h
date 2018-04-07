#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* recebe uma lista de memória livre e o tamanho para ser alocado*/
p_mem aloca_memoria (p_mem mem, int tam);

/* recebe uma lista de memória livre, o endereço de onde se deseja desalocar
 * memório e o tamanho a ser desalocado. */
p_mem desaloca_memoria (p_mem mem, int end, int tam);

/* recebe uma lista de memória livre, o endereço de onde se deseja realocar a
 * memório, o tamanho inicial e o tamanho final. */
p_mem realoca_memoria (p_mem mem, int end, int tam_ini, int tam_final);

/* recebe uma lista de memória livre e imprime o endereço incial do bloco livre
 * e o tamanho desse bloco*/
void imprime_memoria (p_mem mem);