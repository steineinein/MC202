#define DEGRAU_AUMENTO 5 /* Tamanho do degrau de aumento do salário em porcentagem */
#define AUMENTO_GRANDE 3 /* 3 degraus de aumento que é 115% */
#define AUMENTO_MEDIO 2 /* 2 degraus de aumento que é 110% */
#define AUMENTO_PEQUENO 1 /* 1 degraus de aumento que é 105% */
#define AUMENTO_ZERO 0 /* não há aumento */

#include <stdio.h>
#include "lab01.h"

/* Chama a função ler_professor n vezes para ler os dados de n professores */
void ler_professores(Professor *professores, int n){
	int i;
	for (i = 0; i < n; i++){
		ler_professor(professores + i);
	}
}

/* Chama a função ler_alunos n vezes para ler os dados de n alunos */
void ler_alunos(Aluno *alunos, int n)
{
	int i;
	for (i = 0; i < n; i++)
		ler_aluno(alunos + i);
}

/*Retorna 0 se o aluno não curso a disciplina ministrada pelo professor
  retorna 1 se o aluno curso a disciplina ministrada pelo professor*/
int checar_aluno (Aluno aluno, char *disciplina_professor){
	int i;
	for (i = 0; i < aluno.num_disciplinas; i++){
		if (strcmp(aluno.disciplinas[i], disciplina_professor) == 0)
			return 1;
	}
	return 0;
}

/* recebe a média do aluno e o valor do multiplicador, conforme recebe dados
vai alterando o multiplicador de acordo com o valor das médias */
int determina_aumento (double media, int multiplicador){
	/* checa a média e o mulplicador atual (para evitar que um aumento menor se torne grande) */
	if (media == 10.0 && multiplicador == AUMENTO_GRANDE)
		return AUMENTO_GRANDE;
	/* checa a média e o mulplicador atual (para evitar que um aumento menor se torne médio) */
	else if (media >= 9.0 && multiplicador >= AUMENTO_MEDIO)
		return AUMENTO_MEDIO;
	/* checa a média e o mulplicador atual (para evitar um aumento quando não deve existir) */
	else if (media >= 8.5 && multiplicador >= AUMENTO_PEQUENO)
		return AUMENTO_PEQUENO;
	else
		return AUMENTO_ZERO;
}

/* recebe os professores, o numero de professores, os alunos e o numeros de aluno
com base dos resultados dos alunos nas matérias ministradas pelo professor
aumenta o salário do professor. */
void aplicar_aumento(Professor *professores, int np, Aluno *alunos, int na){
	int i, j, multiplicador_aumento;
	/* percorre todos os professores */
	for(i = 0; i < np; i++){
		/* o aumento sempre começa no maior e pode diminuir de acordo com as notas*/
		multiplicador_aumento = AUMENTO_GRANDE;
		/* percorre todos ods alunos */
		for (j = 0; j < na; j++){
			/* checa se o aluno cursa a matéri ministrada pelo professor atual*/
			if (checar_aluno (alunos[j], professores[i].disciplina)){
				/* determina se e quanto o salária deve aumentar */
				multiplicador_aumento = determina_aumento(alunos[j].media, multiplicador_aumento);
			}
		}
		/* aumenta o salário do professor de acordo com o valor calculado. */
		aumento(&professores[i], multiplicador_aumento*DEGRAU_AUMENTO);
	}
}

/* imprime o nome do professor e o novo salário. */
void imprimir_professores(Professor *professores, int np){
	int i;
	for (i = 0; i < np; i++){
		printf("%s ", professores[i].nome);
		printf("%s ", professores[i].sobrenome);
		printf("%.2f\n", professores[i].salario);
	}
}