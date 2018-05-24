 #ifndef ABB_H
 #define ABB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
	char chave[80];
	struct No * esq, * dir, * pai; 
} No;
/*cria um arvore vazia*/
No * criar_arvore();
/* destroi a arvore e seus elementos */
void destruir_arvore(No * raiz);
/*cria um no da arvore*/
No * criar_no(char * chave);
/* insere um elemento na arvore*/
No * inserir(No * raiz, char *chave);
/* remove um elemento da arvore*/
No * remover(No * raiz, char *chave);
/* procurar o minimo da arvore*/
No * minimo(No * raiz);
/* imprime elementos que começem com a chave em ordem*/
void print_autocomplete(No * raiz, char *chave);
/* imprime os elementos da arvore em ordem*/
void print_arvore(No * raiz);
#endif