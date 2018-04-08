#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
/* para imprimir o resultado cria-se uma lista ligada de movimentos
a serem executados */
typedef struct print_node{
	char * text;
	struct print_node * next;
} Print_node;

/* estrutua de pilha de movimentos */
typedef struct {
	Print_node * head, * tail;
} Queue;

/* cria pilha */
Queue * create_queue();

/* recebe uma pilha e a destroí */
void destroy_queue(Queue * queue);

/* enfilera o movimento na pilha */
void enqueue(Queue * q, char * text);

/* retira o movimento da pilha */
char * dequeue(Queue * q);

/* define se é possível realizar o desfile, retorna 0 se não e 1 se é possível
armazena os movimento a ser realizados em de pilha de impressão */
int order_parade(Stack ** v_ruas, Queue * printing_queue, int n_ruas, int n_alegorias);

/* checa se em alguma rua há alguma alegoria que deve entrar no desfile
devolver o número da proxima alegoria que deve desfilar*/
int check_streets(Stack ** v_ruas, Queue * printing_queue, int correct, int n_ruas);

/* acha a quantidade de digitos de um número inteiro*/
int findn(int num);

int main(){
	int n_alegorias, n_ruas, i, possible;
	Stack ** v_ruas;
	char * text;
	Queue * printing_queue;


	scanf("%d %d", &n_alegorias, &n_ruas);
	/* cada rua é representa por uma pilha */
	v_ruas = malloc(n_ruas * sizeof(Stack *));

	for (i = 0; i < n_ruas; i++)
		v_ruas[i] = create_stack();
	printing_queue = create_queue();
	/*`verifica se é possível realizar o desfile */
	possible = order_parade(v_ruas, printing_queue, n_ruas, n_alegorias);
	if (possible == 1){
		printf("Desfile pode ser realizado:\n");
		/* imprime os movimentos do desfile */
		while(printing_queue->head != NULL){
			text = dequeue(printing_queue);
			printf("%s", text);
			free (text);
		}
	}
	else {
		printf("Sem desfile.\n");
		while(printing_queue->head != NULL){
			text = dequeue(printing_queue);
			free (text);
		}
	}

	destroy_queue(printing_queue);
	for (i = 0; i < n_ruas; i++)
		destroy_stack(v_ruas[i]);
	free(v_ruas);

	return 0;
}

int order_parade(Stack ** v_ruas, Queue * printing_queue, int n_ruas, int n_alegorias){
	int i, j, current, correct, possible_flag, top;
	char * text;

	correct = 1;
	for (i = 0; i < n_alegorias; i++){
		scanf("%d", &current);
		/* checa se a alegoria que está entrando na rua é a que deve entrar no desfile */
		if(current == correct){
			/* como o tamanho do vetor pode variar de acordo com o tamnho do inteiro nele,
			calcula-se o número de digitos e adiciona ele ao tamnho*/
			text = (char *) malloc((20 + findn(current)) * sizeof(char));
			sprintf(text, "Alegoria %d desfila.\n", current);
			correct++;
			enqueue(printing_queue, text);
			/* verifica se alguma alegoria que está parada nas ruas pode desfilar */
			correct = check_streets(v_ruas, printing_queue, correct, n_ruas);
		}
		else{
			j = 0;
			possible_flag = 0;
			/* se alegoria não pode desfilar, procura-se alguma rua na qual ela possa
			estacionar e esperar sua vez. Só pode ser armazena em uma pilha em que o 
			a alegoria do topo é maior que ela, caso contrário é impossível realizar o
			desfile na ordem correta */
			while (j < n_ruas){
				top = check_top(v_ruas[j]);
				/* checa se o topo é maior ou se rua está vazia */
				if (current < top || top == 0) {
					push(v_ruas[j], current);
					text = (char *) malloc((36 + findn(current) + findn(j + 1)) * sizeof(char));
					sprintf(text, "Alegoria %d entra na rua %d e aguarda.\n", current, j + 1);
					enqueue(printing_queue, text);
					j = n_ruas;
					possible_flag = 1;
				}
				j++;	
			}
			if (possible_flag == 0){
				for (i = 0; i < n_ruas; i++){
					while (v_ruas[i]->top != NULL)
						pop(v_ruas[i]);
				}
				/* é impossível de realizar o desfile*/
				return 0;
			}		
		}
	}
	/* é possível realizar o desfile */
	return 1;
}

int check_streets(Stack ** v_ruas, Queue * printing_queue, int correct, int n_ruas){
	int i, current;
	char * text;

	for (i = 0; i < n_ruas; i++){
		/* em cada rua verifica se no topo alguma alegoria pode desfilar */
		if (check_top(v_ruas[i])  == correct){
			current = pop(v_ruas[i]);
			text = (char *) malloc((34 + findn(current) + findn(i + 1)) * sizeof(char));
			sprintf(text, "Alegoria %d sai da rua %d e desfila.\n", current, i + 1);
			enqueue(printing_queue, text);
			/* atualiza qual é a proxima alegoria a desfilar */
			correct++;
			/* chama ela mesma recusivamente, para olhar se no novo estado das ruas
			mais alguma alegoria pode desfilar. Atualiza a proxima */
			correct = check_streets(v_ruas, printing_queue, correct, n_ruas);
		}
	}
	return correct;
}

/* cria uma pilha */
 Queue * create_queue(){
	Queue * queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

/* destroí uma pilha */
void destroy_queue(Queue * queue){
	free(queue);
}

/* adiciona um movimento a ser executado na pilha */
void enqueue(Queue * q, char * text){
	Print_node * new;
	new = malloc(sizeof(Print_node));
	new->text = text;
	new->next = NULL;
	if (q->head == NULL)
		q->head = new;
	else
		q->tail->next = new;
	q->tail = new;
}

/* retira um movimento da pilha */
char * dequeue(Queue * q){
	Print_node * first = q->head;
	char * text = first->text;
	q->head = q->head->next;
	if (q->head == NULL)
		q->tail = NULL;
	free(first);
	return text;
}

/* descobro o número de digitos em um número */
int findn(int num){
    int n = 0;
    while(num) {
        num /= 10;
        n++;
    }
    return n;
}