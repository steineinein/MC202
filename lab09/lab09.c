#include "arv_treap.h"

void calcular_resultado_dia(no_treap * transacoes, double taxa);

int main(){
	int n_transf, i;
	long banco;
	double valor_transf, taxa;
	no_treap * transacoes;

	transacoes = criar_treap();

	/* le o número de transações do dia e a taxa de transação */
	scanf("%d %lf", &n_transf, &taxa);

	/* le os dados de cada transação do dia: o banco para qual foi feita a 
	transação e o valor da transação */
	for (i = 0; i < n_transf; i++){
		scanf("%ld %lf", &banco, &valor_transf);
		transacoes = inserir(transacoes, banco, valor_transf);
	}

	/* calcula o valor total das transações para cada banco
	e o total das taxar para cada banco */
	calcular_resultado_dia(transacoes, taxa);

	return 0;
}

void calcular_resultado_dia(no_treap * transacoes, double taxa){
	long banco; 
	double tarifa, valor_total;
	no_treap * transacao;
	/* enquantoo houver transações */
	while(transacoes){
		valor_total = 0;
		tarifa = 0;
		/* procura o banco com o menor identificador */
		banco = minimo(transacoes);
		transacao = busca(transacoes, banco);
/*		enquanto houver transações para esse banco */
		while(transacao){	
			/* Soma o valor das transações, para determinar o total transacionado*/
			valor_total += transacao->valor;
			/*soma as taxas para determinar o total de taxas*/
			tarifa += taxa;
			/* remove essa transação do banco de dados*/
			transacoes = deletar(transacoes, banco);
			/* verifica se há mais transações para esse banco */
			transacao = busca(transacoes, banco);
		}
		printf("Banco %ld R$ %.2f Tarifa R$ %.2f\n", banco, valor_total, tarifa);
	}
}
