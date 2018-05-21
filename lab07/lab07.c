#include "arv_binaria.h"

void checa_cossang(no * arvore1, no * arvore2);

int main(){
	int h1, h2;
	no * arvore1, * arvore2;

	scanf("%d %d", &h1, &h2);
	arvore1 = criar_arvore(0, h1 - 1);
	arvore2 = criar_arvore(0, h2 - 1);
	/* verifica quais pessoas estão em ambas as arvóres e seta a flag de impressão */
	checa_cossang(arvore1, arvore2);
	pre_ordem(arvore1);
	printf("\n");
	pre_ordem(arvore2);
	printf("\n");
	return 0;
}

/*função recursiva para procurar pessoas que estão em ambas as arvores*/
void checa_cossang(no * arvore1, no * arvore2){
	no* aux;
	if(arvore1 == NULL);
	else{
		/* procura a raiz na arcvore 2*/
		aux = procurar_no(arvore2, arvore1->nome);
		if(aux){
			/* se acharem, seta ambos nós para imprimir*/
			arvore1->imprimir = 1;
			aux->imprimir = 1;
		}
		checa_cossang(arvore1->esq, arvore2);
		checa_cossang(arvore1->dir, arvore2);
	}
}
