#include "hash.h"
#include "lista.h"
#include <stdio.h>

int main(){
	char string[51];
	No * aux;
	Hash * tabela;
	tabela = criar_hash();
	/* escaneia cada linha como uma string*/
	while(scanf(" %[^\n]", string) == 1){
		/* se encontrar # para a leitura */
		if (strcmp(string, "#") == 0)
			break;
		else{
			/* procura se a string lida já existe na tabela*/
			aux = buscar(tabela, string);
			/* se não existe na tabela a adiciona e a imprime com 0 na frente */
			if (aux == NULL){
				inserir(tabela, string);
				printf("0 %s\n", string);
			}
			/* se existe só a imprime com 1 na frente*/
			else{
				printf("1 %s\n", string);
			}
		}
	}
	
	destruir_hash(tabela);

	return 0;
}