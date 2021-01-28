#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dblib.h"

void menuTabelas();
void menuBancos();

int main () {
	menuBancos();
	return 0;
}

void menuBancos() {
	char op;
	int i = 1, c;
	database banco;
	banco.numOfTabs = 0;
	banco.name = malloc(sizeof(char) * 50);
	banco.usrRoot = malloc(sizeof(char) * 10);
	banco.pswRoot = malloc(sizeof(char) * 18);
	while (i) {
		printf("Digite o numero referente a opção desejada\n1 - Criar Banco de Dados\t2 - Opções para Bancos exitentes\n3 - Opções para tabelas\t4 - Sair\n\n: ");
		scanf(" %c", &op);
		if (op == '1') {
			printf("Qual o nome do banco a ser criado: ");
			scanf("%s\n", banco.name);
			printf("Escolha um nome de usuário (no maximo 10 carcteres, sem carcteres especiais): ");
			scanf("%s\n", banco.usrRoot);
			printf("Crie uma senha (com no no minimo 8 maximo 18 caracteres: ");
			scanf("%s\n", banco.pswRoot);
			if (criarBanco(&banco))
				printf("Banco de Dados criada com sucesso!\n");
			else
				printf("Erro ao criar Banco de Dados!");
		} else if (op == '2') {
			printf("Digite o numero referente a opção desejada\n1 - Listar todos os Bancos de Dados\t2 - Excluir um Banco de Dados\n3 - Voltar\n\n: ");
			scanf(" %c", &op);
			if (op == '1')
				listarBancos();
			else if (op == '2') {
				c = 3;
				printf("Digite o nome do banco a ser deletado: ");
				scanf("%s\n", banco.name);
				while (c--) {
					printf("Login: ");
					scanf("%s\n", banco.usrRoot);
					printf("Senha: ");
					scanf("%s\n", banco.pswRoot);
					if (autenticar(&banco)) {
						if (deletarBanco(&banco))
							printf("Banco de Dados exluido com sucesso!\n");
						else
							printf("Erro ao exluir Banco de Dados!");
						c = 0;
					}
				}
			} else if (op == '3')
				continue;
			else
				printf("Opção inválida!\n");
		} else if (op == '3')
			menuTabelas(&banco);
		else if (op == '4')
			i = 0;		
		else
			printf("Opção inválida!\n");
	}
	free(banco.name);
	free(banco.usrRoot);
	free(banco.pswRoot);
}

void menuTabelas(database *banco) {
	char op;
	int i = 1, c;
	table tabela;
	tabela.numOfAtts = 0;
	tabela.name = malloc(sizeof(char) * 50);
	while (i) {
		printf("Digite o numero referente a opção desejada\n1 - Opções para administradores\t2 - Opções de consulta\n3 - Voltar\n\n: ");
		scanf(" %c", &op);
		if (op == '1') {
			c = 3;
			printf("Digite o numero referente a opção desejada\n1 - Criar uma tabela\t2 - Deletar uma tabela\t3 - Inserir uma nova linha em uma tabela\t4 - Deletar uma linha em uma tabela\n5 - Voltar\n\n: ");
			scanf(" %c", &op);
			printf("Nome do Banco de Dados: ");
			scanf("%s\n", banco->name);
			while (c--) {
				printf("Login: ");
				scanf("%s\n", banco->usrRoot);
				printf("Senha: ");
				scanf("%s\n", banco->pswRoot);
				if (autenticar(banco)) {
					if (op == '1') {
						printf("Digite o nome da tabela a ser criada: ");
						scanf("%s\n", tabela.name);
						printf("Digite o numero de colunas da tabela (além da chave primaria): ");
						scanf("%d\n", &tabela.numOfAtts);
						tabela.primaryKeyName = malloc(sizeof(char) * 50);
						printf("Digite o nome da coluna a ser conseiderada a chave primaria: ");
						scanf("%s\n", tabela.primaryKeyName);
						tabela.attributes = (char**) malloc(sizeof(char*) * tabela.numOfAtts);
						for (i = 0; i < tabela.numOfAtts; i++)
							tabela.attributes[i] = (char*) malloc(sizeof(char) * 50);
						for (i = 0; i < tabela.numOfAtts; i++) {
							printf("Digite o nome da %da coluna: ", i + 2);
							scanf("%s\n", tabela.attributes[i]);
						}
						if (criarTabela(&tabela, banco))
							printf("Tabela criada com sucesso!\n");
						else
							printf("Erro ao criar tabela!\n");
					}
					c = 0;
				} else
					printf("Usuario e/ou senha errados. Tente novamente! (Mais %d tentativa(s))", c - 1);
			}
		} else if (op == '2') {

		} else if (op == '3')
			i = 0;
		else
			printf("Opção inválida!");
	}
}
