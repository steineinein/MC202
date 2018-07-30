#include "arv_treap.h"

no_treap * criar_treap(){
	return NULL;
}


no_treap * rotacionar_dir(no_treap * y){
	no_treap * x, * T2;
	x = y->esq;
	T2 = x->dir;

	x->dir = y;
	y->esq = T2;

	return x;
}

no_treap * rotacionar_esq(no_treap * x){
	no_treap * y, * T2;
	y = x->dir;
	T2 = y->esq;

	y->esq = x;
	x->dir = T2;

	return y;
}

no_treap * busca(no_treap * raiz, long banco){
	if (raiz == NULL || raiz->banco == banco)
		return raiz;

	if(raiz->banco < banco)
		return busca(raiz->dir, banco);

	return busca(raiz->esq, banco);
}

/* cria novo nó de prioridade aleatória */
no_treap * novo_no(long banco, double valor){
	no_treap * aux;
	aux = malloc(sizeof(no_treap));
	aux->prioriade = rand() % 100;
	aux->banco = banco;
	aux->valor = valor;
	aux->dir = NULL;
	aux->esq = NULL;
	return aux;
}

/* insere valores na treap de forma recursiva */
no_treap * inserir(no_treap * raiz, long banco, double valor){
	if (raiz == NULL)
		return novo_no(banco, valor);
	if(banco <= raiz->banco){
		/* insere na arvore esquerda*/
		raiz->esq = inserir(raiz->esq, banco, valor);
		/* checa se ainda é heap, se não forma rotaciona */
		if (raiz->esq->prioriade > raiz->prioriade)
			raiz = rotacionar_dir(raiz);
	}
	else{
		/* insere na arvore direita*/
		raiz->dir = inserir(raiz->dir, banco, valor);
		/* checa se ainda é heap, se não forma rotaciona */
		if (raiz->dir->prioriade > raiz->prioriade)
			raiz = rotacionar_esq(raiz);
	}
	return raiz;
}

/* deleta valores da treap de forma recursiva */
no_treap * deletar(no_treap * raiz, long banco){
	no_treap * temp;
	if (raiz == NULL)
		return raiz;
	/*`procura o elemento a ser deletado */
	if (banco < raiz->banco)
		raiz->esq = deletar(raiz->esq, banco);
	else if(banco > raiz->banco)
		raiz->dir = deletar(raiz->dir, banco);
	else {
		/* se o elemento tem apenas um filho, remove o elemento e põem o filho no lugar*/
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
		/* se possue dois filho checa as prioridade e rotaciona para manter heap*/
		else if (raiz->esq->prioriade < raiz->dir->prioriade){
			raiz = rotacionar_esq(raiz);
			raiz->esq = deletar(raiz->esq, banco);
		}
		else{
			raiz = rotacionar_dir(raiz);
			raiz->dir = deletar(raiz->dir, banco);
		}
	}
	return raiz;
}

/* encontra o banco com menor identificador*/
double minimo(no_treap * raiz){
	while(raiz != NULL && raiz->esq != NULL)
		raiz = raiz->esq;
	return raiz->banco;
}

/*imprime a arvóre inteira */
void print_arvore(no_treap * raiz){
	if (raiz == NULL);
	else{
		print_arvore(raiz->esq);
		printf("%ld, %f , %d\n", raiz->banco, raiz->valor, raiz->prioriade);
		print_arvore(raiz->dir);
	}
}