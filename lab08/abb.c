#include "abb.h"
/*cria um arvore vazia*/
No * criar_arvore(){
	return NULL;
}

/* destroi a arvore e seus elementos */
void destruir_arvore(No * raiz){
	if (raiz != NULL){
		if (raiz->esq != NULL)
			destruir_arvore(raiz->esq);
		if (raiz->dir != NULL)
			destruir_arvore(raiz->dir);
		free(raiz);
	}
}

/*cria um no da arvore*/
No * criar_no(char * chave){
	No * novo;	
	novo = malloc(sizeof(No));
	novo->esq = novo->dir = NULL;
	strcpy(novo->chave, chave);
	return novo;
}

/* insere um elemento na arvore*/
No * inserir(No * raiz, char *chave){
	if (raiz == NULL) {
		return criar_no(chave);
	}
	/* compara as strings inserindo em ordem lexicográfica​.*/
	if (strcmp(chave, raiz->chave) < 0)
	raiz->esq = inserir (raiz->esq, chave);
	else
	raiz->dir = inserir (raiz->dir, chave);
	return raiz	;
}

/* remove um elemento da arvore*/
No * remover(No * raiz, char * chave){
	No * temp;
	if (raiz == NULL)
		return raiz;
	/* procura o elemento a ser removido, primeiramente na arvore da direita
	depois na arvore da esquerda */
	if (strcmp(raiz->chave, chave) > 0)
		raiz->esq = remover(raiz->esq, chave);
	else if (strcmp(raiz->chave, chave) < 0){
		raiz->dir = remover(raiz->dir, chave);
	}
	else{
		/* possue apenas um filho */
		if (raiz->dir == NULL){
			temp = raiz->esq;
			free(raiz);
			return temp;
		}
		else if (raiz->esq == NULL){
			temp = raiz->dir;
			free(raiz);
			return temp;
		}
		/* possue dois filhos
		substitue o elemento a ser removido pelo seu sucessor
		que é o minimo da arvore da direita, dado que ela existe*/
		temp = minimo(raiz->dir);
		strcpy(raiz->chave, temp->chave);
		raiz->dir = remover(raiz->dir, temp->chave);
	}
	return raiz;
}

/* procurar o minimo da arvore*/
No * minimo(No * raiz){
	/* o minimo é o elemento mais a esquerda da arvore*/
	while (raiz != NULL && raiz->esq != NULL)
		raiz = raiz->esq;
	return raiz;
}

/* imprime elementos que começem com a chave em ordem*/
void print_autocomplete(No * raiz, char *chave){
	if (raiz == NULL);
	/* comparar os n primeiro caracteres da raiz com a chave desejada,
	sendo n o tamanho da chave desejada */
	/* se o elemento satisfazer a condição ele é impressos*/
	else if(strncmp(raiz->chave, chave, strlen(chave)) == 0){
		print_autocomplete(raiz->esq, chave);
		printf("%s\n", raiz->chave);
		print_autocomplete(raiz->dir, chave);
	}
	/* procura ele então nas outras duas arvores */
	else if(strncmp(raiz->chave, chave, strlen(chave)) < 0)
		print_autocomplete(raiz->dir, chave);
	else
		print_autocomplete(raiz->esq, chave);
}

/* imprime os elementos da arvore em ordem*/
void print_arvore(No * raiz){
	if (raiz == NULL);
	else{
		print_arvore(raiz->esq);
		printf("%s\n", raiz->chave);
		print_arvore(raiz->dir);
	}
}