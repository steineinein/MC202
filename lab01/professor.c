#include <stdio.h>
#include "professor.h"

/* função que lê e armazena os dados sobre um professor */
void ler_professor(Professor *professor){
	scanf("%s", professor->nome);
	scanf("%s", professor->sobrenome);
	scanf("%lf", &professor->salario);
	scanf("%s", professor->disciplina);
}

/* função que aumenta o salário de um professor de acordo com a porcentagem recebida */
void aumento(Professor *professor, double porcentagem){
	professor->salario = professor->salario + professor->salario * porcentagem / 100;
}