#include <stdio.h>
#include "aluno.h"


/* função que le e armazena o nome, sobrenome, média, numero de disciplinas cursadas e sua sigla */
void ler_aluno(Aluno *aluno){
	int i;
	scanf("%s", aluno->nome);
	scanf("%s", aluno->sobrenome);
	scanf("%lf", &aluno->media);
	scanf("%d", &aluno->num_disciplinas);
	for (i = 0; i < aluno->num_disciplinas; i++){
		scanf("%s", aluno->disciplinas[i]);		
	}
}