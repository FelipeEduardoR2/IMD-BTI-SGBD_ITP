#include <stdio.h>
#include "dblib.h"

int main () {
	char *nomeDaTabela, *nomeDoBanco = "bancoTeste";
	int qtdAtributos;
	printf("Digite o nome da tabela a ser criada: ");
	scanf("%s", nomeDaTabela);
	printf("Digite o número de conlunas (além da chave primária) da tabela a ser criada: ");
	scanf("%d", &qtdAtributos);
	if (criarTabela(nomeDaTabela, nomeDoBanco, qtdAtributos))
		printf("Tabela criada com sucesso!\n");
	else
		printf("Erro ao criar tabela!");
	listarTabelas(nomeDoBanco);
	return 0;
}
