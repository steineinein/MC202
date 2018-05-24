#include "abb.h"

int main(){
	char op;
	char arg[80];
	No * abb;

	abb = criar_arvore();
	/* enquanto lê um caractere e uma string */
	while (scanf(" %c %[^\n]", &op, arg) == 2) {
		/* adiciona o elemento espcificado a arvore */
		if(op == '+'){
			abb = inserir(abb, arg);
		}
		/* remove o elemento espcificado a arvore */
		else if (op == '-'){
			abb = remover(abb, arg);
		}
		/* imprime todos elementos que começam com o prefixo especificado */
		else if (op == '$'){
			printf("Sugestoes para prefixo \"%s\":\n", arg);
			print_autocomplete(abb, arg);
		}
		/* fim da entrada */
		else if (op == '#' && strcmp(arg, "fim") == 0);
		else
			printf("error\n");
	}

	destruir_arvore(abb);

	return 0;
}