#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tabela {
	char *name, **attributes, *primaryKeyName; //,*usrAdmin, *foreingKey; Ambas informações ainda serão utilizadas.
} table;

int criarTabela(char *nomeDaTabela, char *nomeDoBanco, int qtdAtributos);
//int verificarTabela(char *tabela, char *banco); Função ainda por ser implementada.

int criarTabela(char *nomeDaTabela, char *nomeDoBanco, int qtdAtributos) {
/* Essa parte do código só fará sentido após a implementação da função verificarTabela();
	if (verificarTabela(nomeDaTabela, nomeDoBanco))
		return 0;
	else {
*/
		int i;
		strcat(nomeDoBanco, ".txt");
		table newTable;
		newTable.name = nomeDaTabela;
		printf("Digite o nome da coluna a ser conseiderada a chave primaria: ");
		scanf("%s", newTable.primaryKeyName);
/*	Opção de chave estrangeira será implementada mais adiante.	
		char fk;
		printf("Esta tabela possui chave estrangeira? (\"s\" para sim e \"n\" para não)\n");
		scanf(" %c", &fk);
		if (fk == 's') {
			printf("Digite o nome da chave estrangeira (na tabela original): ");
			scanf("%s", newTable.foreingKey);
		}
*/
		newTable.attributes = (char**) malloc(sizeof(char*) * qtdAtributos);
		for (i = 0; i < qtdAtributos; i++)
			newTable.attributes[i] = (char*) malloc(sizeof(char) * 255);
		for (i = 0; i < qtdAtributos; i++) {
			printf("Digite o nome da %da coluna: ", i + 2);
			scanf("%s", newTable.attributes[i]);
		}
		FILE *file;
		file = fopen(nomeDoBanco, "rw+");
		fprintf(file, "%s\t-\t%d colunas\t-\tPrimary Key: %s\t-\tColunas: ", nomeDaTabela, qtdAtributos, newTable.primaryKeyName);
		for (i = 0; i < qtdAtributos - 1; i++)
			fprintf(file, "%s, ", newTable.attributes[i]);
		fprintf(file, "%s.\n", newTable.attributes[qtdAtributos-1]);
		fclose(file);
		free(newTable.attributes);
		return 1;
//	}
}
