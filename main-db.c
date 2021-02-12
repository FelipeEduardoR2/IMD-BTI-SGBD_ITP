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
		printf("Digite o numero referente a opção desejada\n1 - Criar banco de dados\t2 - Opções para Bancos exitentes\n3 - Opções para tabelas\t4 - Sair\n\n:\t");
		scanf(" %c", &op);
		if (op == '1') {
			printf("Qual o nome do banco a ser criado:\t");
			scanf("%s", banco.name);
			printf("Escolha um nome de usuário (no maximo 10 carcteres, sem carcteres especiais):\t");
			scanf("%s", banco.usrRoot);
			printf("Crie uma senha (com no no minimo 8 maximo 18 caracteres):\t");
			scanf("%s", banco.pswRoot);
			if (criarBanco(&banco)) {
				printf("Banco de dados criado com sucesso!\n\n");
				exit(EXIT_SUCCESS);
			} else
				printf("Erro ao criar banco de dados!\n\n");
		} else if (op == '2') {
			printf("Digite o numero referente a opção desejada\n1 - Listar todos os Bancos de Dados\t2 - Excluir um banco de dados\n3 - Voltar\n\n:\t");
			scanf(" %c", &op);
			if (op == '1')
				listarBancos();
			else if (op == '2') {
				c = 3;
				printf("Digite o nome do banco a ser excluido:\n");
				scanf("%s", banco.name);
				while (c--) {
					printf("Login:\t");
					scanf("%s", banco.usrRoot);
					printf("Senha:\t");
					scanf("%s", banco.pswRoot);
					if (autenticar(&banco)) {
						if (deletarBanco(&banco)) {
							printf("Banco de dados exluido com sucesso!\n\n");
							exit(EXIT_SUCCESS);
						} else
							printf("Erro ao exluir banco de dados!\n\n");
						c = 0;
					}
					printf("Resta(m) %d tentativa(s)\n", c);
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
	int i = 1;
	table tabela;
	tabela.numOfAtts = 0;
	tabela.name = malloc(sizeof(char) * 50);
	while (i) {
		printf("Digite o numero referente a opção desejada\n1 - Opções para administradores\t2 - Opções de consulta\n3 - Voltar\n\n:\t");
		scanf(" %c", &op);
		if (op == '1') {
			printf("Digite o numero referente a opção desejada\n1 - Criar uma tabela\t2 - Inserir uma nova linha em uma tabela\n3 - Excluir uma tabela\t4 - Excluir uma linha em uma tabela\n5 - Voltar\n\n:\t");
			scanf(" %c", &op);
			if (op == '5')
				continue;
			else {
				int c = 3;
				printf("Nome do banco de dados:\t");
				scanf("%s", banco->name);
				while (c--) {
					printf("Login:\t");
					scanf("%s", banco->usrRoot);
					printf("Senha:\t");
					scanf("%s", banco->pswRoot);
					if (autenticar(banco)) {
						printf("Digite o nome da tabela:\t");
						scanf("%s", tabela.name);
						if (verificarTabela(&tabela, banco)) {
							if (op == '1') {
								printf("Digite o numero de colunas da tabela (além da chave primaria):\t");
								scanf("%u", &tabela.numOfAtts);
								tabela.primaryKeyName = malloc(sizeof(char) * 50);
								printf("Digite o nome da coluna a ser conseiderada a chave primaria:\t");
								scanf("%s", tabela.primaryKeyName);
								tabela.attributesName = malloc(sizeof(char) * tabela.numOfAtts);
								for (i = 0; i < tabela.numOfAtts; i++)
									tabela.attributesName[i] = malloc(sizeof(char) * 50);
								tabela.attributesType = malloc(sizeof(char) * tabela.numOfAtts);
								for (i = 0; i < tabela.numOfAtts; i++) {
									printf("Digite o nome da %da coluna:\t", i + 2);
									scanf("%s", tabela.attributesName[i]);
									printf("Escolha um tipo para %da coluna\ni - Inteiro\nr - Real\nc - Caractere alfanumerico unico\nt - Texto (caracteres alfanumericos sem espaço)\n:\t", i + 2);
									scanf(" %c", &tabela.attributesType[i]);
								}
								if (criarTabela(&tabela, banco)) {
									printf("Tabela criada com sucesso!\n\n");
									free(tabela.primaryKeyName);
									free(tabela.attributesName);
									free(tabela.attributesType);
									exit(EXIT_SUCCESS);
								} else {
									printf("Erro ao criar tabela!\n\n");
									free(tabela.primaryKeyName);
									free(tabela.attributesName);
									free(tabela.attributesType);
								}
							} else if (op == '2') {
								if (inserirLinha(&tabela)) {
									printf("Linha inserida com sucesso!\n\n");
									exit(EXIT_SUCCESS);
								} else
									printf("Falha ao inserir linha!\n\n");
							} else if (op == '3') {
								if (deletarTabela(banco, &tabela)) {
									printf("Excluida com sucesso!\n\n");
									exit(EXIT_SUCCESS);
								} else
									printf("Falha ao excluir tabela!\n\n");
							} else if (op == '4') {
								if (deletarLinha(&tabela)) {
									printf("Linha excluida com sucesso!\n\n");
									exit(EXIT_SUCCESS);
								} else
									printf("Falha ao excluir linha!\n\n");
							} else
								printf("Opção inválida, tente novamente!\n\n");
						}
						c = 0;
					} else
						printf("Usuario e/ou senha errados. Tente novamente! (Mais %d tentativa(s))\n", c - 1);
				}
			}
		} else if (op == '2') {
			printf("Digite o numero referente a opção desejada\n1 - Listar todas as tabelas de um banco\t2 - Exibir uma tabela\n3 - Pesquisar valor em uma tabel\t4 - Voltar\n\n: ");
			scanf(" %c", &op);
			if (op == '1') {
				printf("Qual banco de dados deseja exibir:\t");
				scanf("%s", banco->name);
				listarTabelas(banco);
				printf("\n\n");
			} else if (op == '2') {
				printf("Qual tabela deseja exibir:\t");
				scanf("%s", tabela.name);
				exibirTabela(&tabela);
				printf("\n\n");
			} else if (op == '3') {
				printf("Qual tabela deseja exibir:\t");
				scanf("%s", tabela.name);
				pesquisarNaTabela(&tabela);
				printf("\n\n");
			} else if (op == '4')
				continue;
			else
				printf("Opção inválida!\n\n");
		} else if (op == '3')
			i = 0;
		else
			printf("Opção inválida!\n\n");
	}
	free(tabela.name);
}
