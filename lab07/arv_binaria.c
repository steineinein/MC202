#include "arv_binaria.h"

/* criar um arvore genealogica contendo o nome das pessoas e seu graude de
consanguinidade​ com a raiz*/
no* criar_arvore (int h, int hmax){
	no *raiz;
	raiz = malloc(sizeof(no));
	/* chegou ao nivel mais baxio da arvore, não há descendtes abaixo desse nível
	a serem lidos*/
	if (h == hmax){
		raiz->esq = NULL;
		raiz->dir = NULL;
		scanf("%s", raiz->nome);
		raiz->imprimir = 0;
		raiz->cossang = h;
		return raiz;
	}
	/* le a informação em pós orem*/
	raiz->esq = criar_arvore (h + 1, hmax);
	raiz->dir = criar_arvore (h + 1, hmax);
	scanf("%s", raiz->nome);
	raiz->imprimir = 0;
	raiz->cossang = h;
	return raiz;
}

/* procura uma pessoa especifica na arvóre*/
no* procurar_no(no* raiz, char* dado){
	no* esq;
	/* caso base, arvóre é nula ou a raiz é a pessoa procurada */
	if (raiz == NULL || strcmp(raiz->nome, dado) == 0)
		return raiz;
	/* procura do lado direito e depois no lado esquerdo */
	esq = procurar_no(raiz->esq, dado);
	if (esq !=  NULL)
		return esq;
	return procurar_no(raiz->dir, dado);
}

/* imprime as pessoas a serem imprimidas em pré ordem */
void pre_ordem(no* raiz){
	if (raiz){
		if (raiz->imprimir)
			printf("%s %d ", raiz->nome, raiz->cossang);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
		free(raiz);
	}
}