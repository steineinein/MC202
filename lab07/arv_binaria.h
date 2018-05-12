typedef struct No{
	void* dado;
	struct No *esq, *dir;
} no;

no* criar_arvore();

no* procurar_no(no* raiz, void* dado);




