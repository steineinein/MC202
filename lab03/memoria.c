#include "memoria.h"

/* recebe uma lista de memória livre e o tamanho para ser alocado*/
p_mem aloca_memoria (p_mem mem, int tam){
	p_mem end_com_espaco, temp;
	/* busca algum bloco livre como tamanho maior do que quer se alocar*/
	temp = busca_tam_maior_igual(mem, tam);
	end_com_espaco = temp->prox;
	/* se o tamanho do bloco de memório é igual o tamanho de alocação, remove o nó
	 * se não apenas altera seus dados*/
	if (end_com_espaco->tamanho == tam){
		remove_no(temp, end_com_espaco);
	}
	else{
		end_com_espaco->end_ini += tam;
		end_com_espaco->tamanho -= tam;
	}
	return mem;
}

/* recebe uma lista de memória livre, o endereço de onde se deseja desalocar
 * memório e o tamanho a ser desalocado. */
p_mem desaloca_memoria (p_mem mem, int end, int tam){
	p_mem end_ant, end_post;
	/* procura o endereço anterior ao endereço de desalocação */
	end_ant = busca_end_maior(mem, end);
	/* caso do endereço de desalocação para frente tudo esteja alocado
	 * adiciona um nó com esse endereço e o tamanho desalocado*/
	if (end_ant->prox == NULL){
		adiciona_no(end_ant, cria_no(end, tam));
		return mem;
	}
	end_post = end_ant->prox;
	/* caso o espaço a ser desalocado não faça fronteira com uma parte livre
	 * adiciona um nó com o edenreço e tamanho desalocado. */
	if ((end_ant->end_ini + end_ant->tamanho < end) && (end_post->end_ini > end + tam)){
		adiciona_no(end_ant, cria_no(end, tam));
		return mem;	
	}
	/* caso o espaço a ser desalocado faça fronteira de ambos os lados com um parte livre
	 * funde as duas partes livres em uma*/
	else if ((end_ant->end_ini + end_ant->tamanho == end) && (end_post->end_ini == end + tam)){
		end_ant->tamanho = end_ant->tamanho + tam +end_post->tamanho;
		remove_no(end_ant, end_post);
		return mem;
	}
	/* caso o espaço a ser desalocado faça fronteira com um parte livre na parte inicial
	 * altera o nó anterior */
	else if (end_ant->end_ini + end_ant->tamanho == end){
		end_ant->tamanho += tam;
		return mem;
	}
	/* caso o espaço a ser desalocado faça fronteira com um parte livre na parte final
	 * altera o nó posterior */
	else{
		end_post->end_ini -= tam;
		end_post->tamanho += tam;
		return mem;
	}
}

/* recebe uma lista de memória livre, o endereço de onde se deseja realocar a
 * memório, o tamanho inicial e o tamanho final. */
p_mem realoca_memoria (p_mem mem, int end, int tam_ini, int tam_final){
	p_mem end_ant, end_post;
	/* se tamanho incial iguala final não faça nada*/
	if (tam_ini == tam_final)
		return mem;
	/* procura o endereço anterior ao endereço de realocação */
	end_ant = busca_end_maior(mem, end);
	/* se o tamanho final é menor que o incial é necessário apenas desalocar
	 * a diferença*/
	if (tam_final < tam_ini){
		desaloca_memoria(mem, end + tam_final, tam_ini - tam_final);
		return mem;
	}
	/* para tamanho final maior que inicial*/
	/* se o bloco a ser desalocado for o ultimo bloco ocupado
	 * procura um espaço para alocação no vetor e depois desaloca
	 * o antigo */
	else if (end_ant->prox == NULL){
		aloca_memoria(mem, tam_final);
		desaloca_memoria(mem, end, tam_ini);
		return mem;
	}
	end_post = end_ant->prox;
	/* verifica se no final do bloco inicial existe espaço livre que comporta 
	 * o novo tamanho se sim, aloca esse espaço */
	if ((end_post->end_ini + end_post->tamanho >= end + tam_final) && (end + tam_ini == end_post->end_ini)){
		aloca_memoria(end_ant, tam_final - tam_ini);
		return mem;
	}
	/* se não existe, procura no resto da lista um espaço que o comporte
	 * e então desaloca o antigo*/
	else{
		aloca_memoria(mem, tam_final);
		desaloca_memoria(mem, end, tam_ini)		;
		return mem;
	}
}

/* recebe uma lista de memória livre e imprime o endereço incial do bloco livre
 * e o tamanho desse bloco*/
void imprime_memoria (p_mem mem){
	while (mem->prox != NULL){
		printf("(%d, %d)\n", mem->prox->end_ini, mem->prox->tamanho);
		mem = mem->prox;
	}
}