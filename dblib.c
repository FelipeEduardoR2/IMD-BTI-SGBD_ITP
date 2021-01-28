#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dblib.h"

void listarBancos() {
	int i = 1;
	FILE *fileMainDB;
	char aux1, *aux2, nomeArquivo[11] = "main-db.txt";
	fileMainDB = fopen(nomeArquivo, "r");
	while (i) {
		fscanf(fileMainDB, " %c", &aux1);
		if (aux1 == '>') {
			aux2 = malloc(sizeof(char) * 50);
			fscanf(fileMainDB, "%s\n", aux2);
			printf("%s\n", aux2);
			free(aux2);
		} else
			i = 0;
	}
	fclose(fileMainDB);
}

void exibirTabela(table *tabela) {
	int i, qtdLinhas;
	FILE *arquivoTB;
	char *nomeArquivo, *linhaAtual;
	nomeArquivo = malloc(sizeof(char) * 54);
	nomeArquivo = tabela->name;
	strcat(nomeArquivo, ".txt");
	arquivoTB = fopen(nomeArquivo, "rw");
	free(nomeArquivo);
	if (arquivoTB == NULL) {
		fclose(arquivoTB);
		printf("Erro ao abrir tabela!");
	} else {
		fscanf(arquivoTB, "%d colunas, %d linha preencidas.\n", &tabela->numOfAtts, &qtdLinhas);
		linhaAtual = malloc(sizeof(char) * 550);
		while (qtdLinhas--) {
			fscanf(arquivoTB, "%s\n", linhaAtual);
			printf("%s\n", linhaAtual);
		}
		free(linhaAtual);
		fclose(arquivoTB);
	}
}

void listarTabelas(database *banco) {
	int i, c = 1;
	char aux, *nomeDoBanco;
	table tabelaImprimir;
	FILE *arquivoBD;
	tabelaImprimir.name = malloc(sizeof(char) * 54);
	tabelaImprimir.primaryKeyName = malloc(sizeof(char) * 54);
	nomeDoBanco = malloc(sizeof(char) * 54);
	strcat(nomeDoBanco, ".txt");
	arquivoBD = fopen(nomeDoBanco, "r");
	printf("Nome\t-\tColunas\t-\tChave Primaria\t-\tDemais atributos\n");
	while (c) {
		fscanf(arquivoBD, " %c", &aux);
		if (aux == '>') {
			fscanf(arquivoBD, "%s\t-\t%d colunas\t-\tPrimary Key: %s\t-\tColunas: ", tabelaImprimir.name, &tabelaImprimir.numOfAtts, tabelaImprimir.primaryKeyName);
			tabelaImprimir.attributes = (char**) malloc(sizeof(char*) * tabelaImprimir.numOfAtts);
			for (i = 0; i < tabelaImprimir.numOfAtts; i++)
				tabelaImprimir.attributes[i] = (char*) malloc(sizeof(char) * 50);
			for (i = 0; i < tabelaImprimir.numOfAtts - 1; i++)
				fscanf(arquivoBD, "%s, ", tabelaImprimir.attributes[i]);
			fscanf(arquivoBD, "%s.\n", tabelaImprimir.attributes[tabelaImprimir.numOfAtts - 1]);
			printf("%s\t-\t%d colunas\t-\tPrimary Key: %s\t-\tColunas: ", tabelaImprimir.name, tabelaImprimir.numOfAtts, tabelaImprimir.primaryKeyName);
			for (i = 0; i < tabelaImprimir.numOfAtts - 1; i++)
				fscanf(arquivoBD, "%s, ", tabelaImprimir.attributes[i]);
			printf("%s.\n", tabelaImprimir.attributes[tabelaImprimir.numOfAtts - 1]);
			free(tabelaImprimir.attributes);
		} else
			c = 0;
	}
	fclose(arquivoBD);
	free(tabelaImprimir.attributes);
}

/* Função ainda não implementada
void pesquisarNaTabela(table *tabela) {

}*/

int criarBanco(database *banco) {
	int i;
	FILE *arqNovoBD, *arquivo;
	char *nomeArqNovoDB = banco->name, nomeArquivo[11] = "main-db.txt";
	arquivo = fopen(nomeArquivo, "a+");
	fprintf(arquivo, ">%s\t-\t%d tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", banco->name, banco->numOfTabs, banco->usrRoot, banco->pswRoot);
	strcat(banco->name, ".txt");
	arqNovoBD = fopen(banco->name, "r+");
	if (arquivo == NULL || arqNovoBD == NULL) {
		fclose(arquivo);
		fclose(arqNovoBD);
		return 0;
	} else {
		fclose(arquivo);
		fclose(arqNovoBD);
		return 1;
	}
}

int autenticar(database *banco) {
	// Função ainda não implementada
	return 1;
}

int deletarTabela(table *tabela) {
	// Função ainda não implementada
	return 0;
}

int deletarBanco(database *banco) {
	int i = 1, totalBancos = 0, numBanco;
	FILE *fileMainDB;
	char aux1, *aux2, *aux3, **todosBancos, nomeArquivo[11] = "main-db.txt";
	fileMainDB = fopen(nomeArquivo, "r");
	while (i) {
		fscanf(fileMainDB, " %c", &aux1);
		if (aux1 == '>') {
			totalBancos++;
			aux2 = malloc(sizeof(char) * 50);
			aux3 = malloc(sizeof(char) * 500);
			fscanf(fileMainDB, "%s\t%s\n", aux2, aux3);
			if (!strcmp(aux3, banco->name))
				numBanco = totalBancos;
			free(aux2);
			free(aux3);
		} else {
			i = 0;
			fclose(fileMainDB);
		}
	}
	todosBancos = malloc(sizeof(char) * totalBancos);
	for ( ; i < totalBancos; i++)
		todosBancos[i] = malloc(sizeof(char) * 550);
	fileMainDB = fopen(nomeArquivo, "w+");
	for (i = 0; i < totalBancos; i++) {
		if (i == numBanco)
			continue;
		else
			fprintf(fileMainDB, "%s\n", todosBancos[i]);
	}
	free(todosBancos);
	fclose(fileMainDB);
	return 0;
}

int inserirLinha(line *tupla, table *tabela) {
	int i, qtdLinhas;
	FILE *arquivoTB;
	char *nomeArquivo, *linhaAtual;
	nomeArquivo = malloc(sizeof(char) * 54);
	nomeArquivo = tabela->name;
	strcat(nomeArquivo, ".txt");
	arquivoTB = fopen(nomeArquivo, "rw");
	if (arquivoTB == NULL) {
		fclose(arquivoTB);
		free(nomeArquivo);
		return 0;
	} else {
		fscanf(arquivoTB, "%d colunas, %d linha preencidas.\n", &tabela->numOfAtts, &qtdLinhas);
		linhaAtual = malloc(sizeof(char) * 550);
		while (qtdLinhas--)
			fscanf(arquivoTB, "%s\n", linhaAtual);
		free(linhaAtual);
		fprintf(arquivoTB, "%u\t-\t", tupla->primaryKeyValue);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivoTB, "%s\t-\t", tupla->attributes[i]);
		fprintf(arquivoTB, "%s.\n", tupla->attributes[tabela->numOfAtts-1]);
		fclose(arquivoTB);
		free(nomeArquivo);
		return 1;
	}
}

int deletarLinha(line *tupla, table *tabela) {
	// Função ainda não implementada
	return 0;
}

int criarTabela(table *tabela, database *banco) {
	int i;
	FILE *arquivoBD, *arquivoTB;
	char *nomeArquivo;
	if ((verificarTabela(tabela, banco))) {
		nomeArquivo = malloc(sizeof(char) * 54);
		nomeArquivo = banco->name;
		strcat(nomeArquivo, ".txt");
		arquivoBD = fopen(nomeArquivo, "a");
		fprintf(arquivoBD, ">%s\t-\t%d colunas\t-\tPrimary Key: %s\t-\tColunas: ", tabela->name, tabela->numOfAtts, tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivoBD, "%s, ", tabela->attributes[i]);
		fprintf(arquivoBD, "%s.\n", tabela->attributes[tabela->numOfAtts-1]);
		fclose(arquivoBD);
		nomeArquivo = tabela->name;
		strcat(nomeArquivo, ".txt");
		arquivoTB = fopen(nomeArquivo, "w+");
		fprintf(arquivoTB, "%d colunas, %d linha preencidas.\n", tabela->numOfAtts + 1, 0);
		fclose(arquivoTB);
		free(nomeArquivo);
		return 1;
	}
	else
		return 0;
}

int verificarTabela(table *tabela, database *banco) {
	int i, c = banco->numOfTabs;
	char *auxLinhaTab, *auxNomeTab;
	strcat(banco->name, ".txt");
	FILE *arquivoBD;
	arquivoBD = fopen(banco->name, "r");
	if (arquivoBD == NULL) {
		printf("Erro ao abrir banco de dados, verifique os valores informados e tente novamente!");
		fclose(arquivoBD);
		return 0;
	} else {
		auxLinhaTab = malloc(sizeof(char) * 510);
		auxNomeTab = malloc(sizeof(char) * 50);
		while (c) {
			fscanf(arquivoBD, ">%s\t-\t%s\n", auxNomeTab, auxLinhaTab);
			if (strcmp(auxNomeTab, tabela->name))
				c--;
			else {
				printf("Já existe uma tabela com esse nome!\n");
				fclose(arquivoBD);
				free(auxNomeTab);
				free(auxLinhaTab);
				return 0;
			}
		}
		fclose(arquivoBD);
		free(auxNomeTab);
		free(auxLinhaTab);
		return 1;
	}
}
