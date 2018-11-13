#include "dblib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void listarTabelas(char *nomeDoBanco) {
	int i, c = 1;
	char aux;
	table tabelaImprimir;
	printf("Nome\t-\tColunas\t-\tChave Primaria\t-\tDemais atributos");
	strcat(nomeDoBanco, ".txt");
	FILE *file;
	file = fopen(nomeDoBanco, "r");
	while (c) {
		scanf(" %c", &aux);
		if (aux == '>') {
			fscanf(file, "%s\t-\t%d colunas\t-\tPrimary Key: %s\t-\tColunas: ", 					tabelaImprimir.name, &tabelaImprimir.numOfAtt,	tabelaImprimir.primaryKeyName);
			tabelaImprimir.attributes = (char**) malloc(sizeof(char*) * tabelaImprimir.numOfAtt);
			for (i = 0; i < tabelaImprimir.numOfAtt; i++)
				tabelaImprimir.attributes[i] = (char*) malloc(sizeof(char) * 255);
			for (i = 0; i < tabelaImprimir.numOfAtt - 1; i++) {
				fscanf(file, "%s, ", tabelaImprimir.attributes[i]);
			}
			fscanf(file, "%s.\n", tabelaImprimir.attributes[tabelaImprimir.numOfAtt - 1]);
			free(tabelaImprimir.attributes);
		} else
			c = 0;
	}
	fclose(file);
	free(tabelaImprimir.attributes);
}
