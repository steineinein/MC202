#ifndef HASH_H
#define HASH_H
#include "lista.h"
#define MAX 500


typedef struct{
	No * v[MAX];	
} Hash;

/* cria uma tabela de hash vazia*/
Hash * criar_hash();

/* destroi a tabela de hash */
void destruir_hash(Hash * tabela);

/* insere o novo elmento na tabela */
void inserir(Hash * tabela, char * chave);

/*void remover(Hash * tabela, char * chave);
*/

/* busca um certo elemento na tabela, se ele não existe retorna NULL */
No * buscar(Hash * tabela, char * chave);

void imprimir_hash(Hash * tabela);

#endif