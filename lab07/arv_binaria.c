no* criar_arvore (int h){
	raiz = malloc(sizeof(no));
	if (h = 1){
		raiz->esq = NULL;
		raiz->dir = NULL;
		scanf("%s", raiz->dados);
		return raiz;
	}
	raiz->esq = criar_arvore (h - 1);
	raiz->dir = criar_arvore (h - 1);
	scanf("%s", raiz->dados);

}
