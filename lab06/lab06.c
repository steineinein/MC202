#include "fila_prioridade.h"
#include <stdio.h>

typedef struct{
	int id, n_clock, prioridade, dependencia;
}Proc;

typedef struct{
	int id, processos_id, end_clock;
}Nucleo;

int comparar_proc(void*, void*);
int comparar_proc_depend(void*, void*);
int comparar_nucleo_parado(void*, void*);
int comparar_nucleo_trabalhando(void* nucleo_1, void* nucleo_2);

void limpa_nucleo(FP * fila_nucleo_parado);
Proc * criar_processo(int id, int n_clock, int prioridade, int dependencia);
Nucleo * criar_nucleo(int id, int processos_id, int end_clock);
FP * altera_dependencias(FP * fila_processos, FP * fila_processos_dependentes, int processo_terminado_id);

int main (){
	int n_nucleos, n_processos, i, id, n_clock, prioridade, dependencia, clock_atual;
	Proc * proc;
	Nucleo * nucleo;
	FP * fila_nucleo_parado, * fila_nucleo_trabalhando;
	FP * fila_processos, * fila_processos_dependentes;

	scanf("%d %d", &n_nucleos, &n_processos);
	fila_processos = criar_filaprio(n_processos, comparar_proc);
	fila_processos_dependentes = criar_filaprio(n_processos, comparar_proc_depend);
	fila_nucleo_parado = criar_filaprio(n_nucleos, comparar_nucleo_parado);
	fila_nucleo_trabalhando = criar_filaprio(n_nucleos, comparar_nucleo_trabalhando);

	for (i = 0; i < n_nucleos; i++){
		nucleo = criar_nucleo(i, 0, 0);
		inserir(fila_nucleo_parado, nucleo);
	}

	for (i = 0; i < n_processos; i++){
		scanf("%d %d %d %d", &id, &n_clock, &prioridade, &dependencia);
		proc = criar_processo(id, n_clock, prioridade, dependencia);
		if(proc->dependencia == 0)
			inserir(fila_processos, proc);
		else
			inserir(fila_processos_dependentes, proc);
	}

	clock_atual = 0;
	while(!vazia(fila_processos) || !vazia(fila_processos_dependentes)){
		while(!vazia(fila_processos) && !vazia(fila_nucleo_parado)){
			proc = extrair_maximo(fila_processos);
			nucleo = extrair_maximo(fila_nucleo_parado);
			nucleo->processos_id = proc->id;
			nucleo->end_clock = clock_atual  + proc->n_clock;
			inserir(fila_nucleo_trabalhando, nucleo);
			printf("processo %d iniciou no clock %d\n", proc->id, clock_atual);
			free(proc);
		}
		nucleo = extrair_maximo(fila_nucleo_trabalhando);
		clock_atual = nucleo->end_clock;
		printf("processo %d encerrou no clock %d\n", nucleo->processos_id, clock_atual);
		fila_processos_dependentes = altera_dependencias(fila_processos, fila_processos_dependentes, nucleo->processos_id);
		inserir(fila_nucleo_parado, nucleo);
		while(!vazia(fila_nucleo_trabalhando) && nucleo->end_clock == clock_atual){
			nucleo = extrair_maximo(fila_nucleo_trabalhando);
			if (nucleo->end_clock == clock_atual){
				printf("processo %d encerrou no clock %d\n", nucleo->processos_id, clock_atual);
				fila_processos_dependentes = altera_dependencias(fila_processos, fila_processos_dependentes, nucleo->processos_id);
				inserir(fila_nucleo_parado, nucleo);
			}
			else
				inserir(fila_nucleo_trabalhando, nucleo);
		}
	}
	while(!vazia(fila_nucleo_trabalhando)){
		nucleo = extrair_maximo(fila_nucleo_trabalhando);
		clock_atual = nucleo->end_clock;
		printf("processo %d encerrou no clock %d\n", nucleo->processos_id, clock_atual);
		inserir(fila_nucleo_parado, nucleo);
	}

	limpa_nucleo(fila_nucleo_parado);
	destroir_filaprio(fila_nucleo_trabalhando);
	destroir_filaprio(fila_nucleo_parado);
	destroir_filaprio(fila_processos);
	destroir_filaprio(fila_processos_dependentes);	
	return(0);
}

FP * altera_dependencias(FP * fila_processos, FP * fila_processos_dependentes, int processo_terminado_id){
		Proc * proc;
		FP * fila_processos_dependentes_aux;
		fila_processos_dependentes_aux = criar_filaprio(fila_processos_dependentes->tamanho, comparar_proc_depend);
		while(!vazia(fila_processos_dependentes)){
			proc = extrair_maximo(fila_processos_dependentes);
			if(proc->dependencia == processo_terminado_id){
				proc->dependencia = 0;
				inserir(fila_processos, proc);
			}
			else
				inserir(fila_processos_dependentes_aux, proc);
		}
		destroir_filaprio(fila_processos_dependentes);
		return fila_processos_dependentes_aux;
}


Proc * criar_processo(int id, int n_clock, int prioridade, int dependencia){
	Proc * proc = malloc(sizeof(Proc));
	proc->id = id;
	proc->n_clock = n_clock;
	proc->prioridade = prioridade;
	proc->dependencia = dependencia;
	return proc;
}

Nucleo * criar_nucleo(int id, int processos_id, int end_clock){
	Nucleo * nucleo = malloc(sizeof(Nucleo));
	nucleo->id = id;
	nucleo->processos_id = processos_id;
	nucleo->end_clock = end_clock;
	return nucleo;
}

void limpa_nucleo(FP * fila_nucleo_parado){
	while(!vazia(fila_nucleo_parado))
		free(extrair_maximo(fila_nucleo_parado));
}

int comparar_proc(void* proc_1, void* proc_2){
	if (((Proc *)proc_1)->prioridade < ((Proc *)proc_2)->prioridade)
		return - 1;
	else if(((Proc *)proc_1)->prioridade > ((Proc *)proc_2)->prioridade)
		return 1;
	else{
		if(((Proc *)proc_1)->id > ((Proc *)proc_2)->id)
			return - 1;
		else
			return 1;
	}
}

int comparar_proc_depend(void* proc_1, void* proc_2){
	return 0;
}

int comparar_nucleo_parado(void* nucleo_1, void* nucleo_2){
	if(((Nucleo *)nucleo_1)->id < ((Nucleo *)nucleo_2)->id)
		return 1;
	else
		return -1;
}

int comparar_nucleo_trabalhando(void* nucleo_1, void* nucleo_2){
	if(((Nucleo *)nucleo_1)->end_clock < ((Nucleo *)nucleo_2)->end_clock)
		return 1;
	else if (((Nucleo *)nucleo_1)->end_clock > ((Nucleo *)nucleo_2)->end_clock)
		return -1;
	else{
		if(((Nucleo *)nucleo_1)->id < ((Nucleo *)nucleo_2)->id)
			return 1;
		else
			return -1;
	}
}