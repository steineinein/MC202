#define MAX_PROFESSOR 100
#define MAX_ALUNOS 200
#include "lab01.h"

int main()
{
	int np, na;
	Professor professores[MAX_PROFESSOR];
	Aluno alunos[MAX_ALUNOS];

	scanf("%d", &np);

	ler_professores(professores, np);

	scanf("%d", &na);

	ler_alunos(alunos, na);

	aplicar_aumento(professores, np, alunos, na);

	imprimir_professores(professores, np);
	return 0;
}