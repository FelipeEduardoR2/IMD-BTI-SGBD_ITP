#include "dblib.h"

void listarBancos() {
	int i = 1, qtdBancos;
	FILE *arquivo;
	database banco;
	arquivo = fopen("sgbd-itp.db", "r");
	fscanf(arquivo, "%d bancos\n", &qtdBancos);
	if (qtdBancos) {
		banco.name = malloc(sizeof(char) * 50);
		banco.usrRoot = malloc(sizeof(char) * 10);
		banco.pswRoot = malloc(sizeof(char) * 18);
		printf("\tNome\t-\tTabelas\t-\tUsuário Admin\n");
		while (qtdBancos--) {
			fscanf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", banco.name, &banco.numOfTabs, banco.usrRoot, banco.pswRoot);
			printf("%s\t-\t\t%u\t-\t%s\n", banco.name, banco.numOfTabs, banco.usrRoot);
		}
		free(banco.name);
		free(banco.usrRoot);
		free(banco.pswRoot);
		fclose(arquivo);
	} else {
		printf("Não há bancos para serem listados!\n");
		fclose(arquivo);
	}
}

void exibirTabela(table *tabela) {
	line tupla;
	FILE *arquivo;
	int i, qtdLinhas;
	string nomeArquivo;
	nomeArquivo = malloc(sizeof(char) * 53);
	strcpy(nomeArquivo, tabela->name);
	strcat(nomeArquivo, ".tb");
	arquivo = fopen(nomeArquivo, "r");
	free(nomeArquivo);
	if (arquivo == NULL) {
		fclose(arquivo);
		printf("Erro ao abrir tabela!");
	} else {
		fscanf(arquivo, "%u colunas, %d linhas preencidas\n", &tabela->numOfAtts, &qtdLinhas);
		tabela->numOfAtts--;
		tabela->primaryKeyName = malloc(sizeof(char) * 50);
		tabela->attributesName = malloc(sizeof(char) * tabela->numOfAtts);
		for (i = 0; i < tabela->numOfAtts; i++)
			tabela->attributesName[i] = malloc(sizeof(char) * 50);
		fscanf(arquivo, "%s\t-\t", tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fscanf(arquivo, "%s\t-\t", tabela->attributesName[i]);
		fscanf(arquivo, "%s\n", tabela->attributesName[tabela->numOfAtts - 1]);
		printf("%s\t-\t", tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			printf("%s\t-\t", tabela->attributesName[i]);
		printf("%s\n", tabela->attributesName[tabela->numOfAtts - 1]);
		free(tabela->attributesName);
		free(tabela->primaryKeyName);
		tupla.attributes = malloc(sizeof(char) * tabela->numOfAtts);
		for (i = 0; i < tabela->numOfAtts; i++)
			tupla.attributes[i] = malloc(sizeof(char) * 50);
		while (qtdLinhas--) {
			fscanf(arquivo, "%u\t-\t", &tupla.primaryKeyValue);
			for (i = 0; i < tabela->numOfAtts - 1; i++)
				fscanf(arquivo, "%s\t-\t", tupla.attributes[i]);
			fscanf(arquivo, "%s\n", tupla.attributes[tabela->numOfAtts - 1]);
			printf("%u\t-\t", tupla.primaryKeyValue);
			for (i = 0; i < tabela->numOfAtts - 1; i++)
				printf("%s\t-\t", tupla.attributes[i]);
			printf("%s\n", tupla.attributes[tabela->numOfAtts - 1]);
		}
		fclose(arquivo);
		free(tupla.attributes);
	}
}

void listarTabelas(database *banco) {
	table tabela;
	FILE *arquivo;
	int i, qtdTabelas;
	string nomeDoBanco;
	nomeDoBanco = malloc(sizeof(char) * 53);
	nomeDoBanco = banco->name;
	strcat(nomeDoBanco, ".db");
	arquivo = fopen(nomeDoBanco, "r");
	fscanf(arquivo, "%d tabelas", &qtdTabelas);
	printf("\tNome\t-\tColunas\t-\tChave Primaria\n");
	tabela.name = malloc(sizeof(char) * 50);
	tabela.primaryKeyName = malloc(sizeof(char) * 50);
	while (qtdTabelas--) {
		fscanf(arquivo, "%s\t-\t%u colunas\t-\tChave Primaria: %s	-	Colunas: ", tabela.name, &tabela.numOfAtts, tabela.primaryKeyName);
		printf("%s\t\t-\t%u\t\t-\t%s\n", tabela.name, tabela.numOfAtts, tabela.primaryKeyName);
		tabela.attributesName = malloc(sizeof(char) * tabela.numOfAtts);
		for (i = 0; i < tabela.numOfAtts; i++)
			tabela.attributesName[i] = malloc(sizeof(char) * 50);
		tabela.attributesType = malloc(sizeof(char) * tabela.numOfAtts);
		for (i = 0; i < (int) tabela.numOfAtts - 2; i++) {
			fscanf(arquivo, "%s (%c), ", tabela.attributesName[i], &tabela.attributesType[i]);
		}
		fscanf(arquivo, "%s (%c)\n", tabela.attributesName[tabela.numOfAtts - 1], &tabela.attributesType[tabela.numOfAtts - 1]);
		free(tabela.attributesName);
		free(tabela.attributesType);
	}
	fclose(arquivo);
	free(nomeDoBanco);
	free(tabela.name);
	free(tabela.primaryKeyName);
}

void pesquisarNaTabela(table *tabela) {
	FILE *arquivo;
	string nomeArquivo;
	nomeArquivo = malloc(sizeof(char) * 53);
	strcpy(nomeArquivo, tabela->name);
	strcat(nomeArquivo, ".tb");
	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir tabela!\n\n");
		free(nomeArquivo);
		fclose(arquivo);
	} else {
		line tuplaTemp;
		char opPesquisa;
		date dadoTemp, dadoPesquisa;
		int i, c, j, qtdLinhas, colunaPesquisa;
		fscanf(arquivo, "%u colunas, %d linhas preenchidas", &tabela->numOfAtts, &qtdLinhas);
		tabela->primaryKeyName = malloc(sizeof(char) * 50);
		tabela->attributesName = malloc(sizeof(char) * --tabela->numOfAtts);
		for (i = 0; i < tabela->numOfAtts; i++)
			tabela->attributesName[i] = malloc(sizeof(char) * 50);
		tabela->attributesType = malloc(sizeof(char) * tabela->numOfAtts);
		fscanf(arquivo, "%s\t-\t", tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fscanf(arquivo, "%s (%c)\t-\t", tabela->attributesName[i], &tabela->attributesType[i]);
		fscanf(arquivo, "%s\n", tabela->attributesName[tabela->numOfAtts - 1]);
		printf("Em qual coluna deseja fazer a pesquisa:\n");
		printf("%d - %s\n", 1, tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts; i++)
			printf("%d - %s\n", i + 2, tabela->attributesName[i]);
		printf(": ");
		scanf("%d", &colunaPesquisa);
		if (colunaPesquisa == 1)
			dadoPesquisa.type = 'u';
		else
			dadoPesquisa.type = tabela->attributesType[colunaPesquisa - 2];
		dadoTemp.type = dadoPesquisa.type;
		dadoPesquisa.value = malloc(sizeof(char) * 50);
		while (1) {
			printf("Digite o valor a ser pesquisado: ");
			scanf("%s", dadoPesquisa.value);
			if (validarDado(&dadoPesquisa)) {
				printf("Escolha uma opção de pesquisa:\n1 - Valores maiores que o valor informado\t2 - Valores maiores ou iguais ao valor informado\n3 - Valores iguais ao valor informado\t4 - Valores menores que o valor informado\n 5 - Valores menores ou iguais ao valor informado");
				if (dadoPesquisa.type == 't')
					printf("\t6 - Valores próximos ao valor informado");
				printf("\n:\t");
				scanf(" %c", &opPesquisa);			
				tuplaTemp.attributes = malloc(sizeof(char) * tabela->numOfAtts);
				for (i = 0; i < tabela->numOfAtts; i++)
					tuplaTemp.attributes[i] = malloc(sizeof(char) * 50);
				c = qtdLinhas;
				while (c--) {
					fscanf(arquivo, "%u\t-\t", &tuplaTemp.primaryKeyValue);
					for (i = 0; i < tabela->numOfAtts - 1; i++)
						fscanf(arquivo, "%s\t-\t", tuplaTemp.attributes[i]);
					fscanf(arquivo, "%s\n", tuplaTemp.attributes[tabela->numOfAtts - 1]);
					dadoTemp.value = tuplaTemp.attributes[colunaPesquisa - 2];
					if (compararDados(opPesquisa, &dadoTemp, &dadoPesquisa)) {
						printf("Valor encontrado na linha %d:\n%u\t-\t", qtdLinhas - c, tuplaTemp.primaryKeyValue);
						for (i = 0; i < tabela->numOfAtts - 1; i++)
							printf("%s\t-\t", tuplaTemp.attributes[i]);
						printf("%s\n", tuplaTemp.attributes[tabela->numOfAtts - 1]);
					}
				}
				free(tuplaTemp.attributes);
				break;
			}
		}
		free(dadoPesquisa.value);
		free(tabela->primaryKeyName);
		free(tabela->attributesName);
		free(tabela->attributesType);
	}
	fclose(arquivo);
	free(nomeArquivo);
}

int validarDado(date *dado) {
	int i;
	if (dado->type == 'p') {
		if (strlen(dado->value) != 4) {
			printf("A chave primaria deve conter exatamente quatro digitos.\nVerifique o valor informado e tente novamente!\n\n");
			return 0;
		} else {
			for (i = 0; i < 4; i++) {
				if (!isdigit(dado->value[i])) {
					printf("A chave primaria deve ser um valor inteiro sem sinal.\nVerifique o valor informado e tente novamente!\n\n");
					return 0;
				}
			}
		}
	} else if (dado->type == 'i') {
		for (i = 0; i < strlen(dado->value); i++) {
			if (!isdigit(dado->value[i])) {
				printf("O valor não é um numero inteiro.\nVerifique o valor informado e tente novamente!\n\n");
				return 0;
			}
		}
	} else if (dado->type == 'r') {
		int ponto = 0;
		for (i = 0; i < strlen(dado->value); i++) {
			if (isdigit(dado->value[i]))
				continue;
			else if (dado->value[i] == '.') {
				ponto++;
				continue;
			} else {
				printf("O valor não é um numero real (as frações são desconsideradas aqui).\nVerifique o valor informado e tente novamente!\n\n");
				return 0;
			}
		}
		if (ponto == 1)
			return 1;
		else {
			printf("O valor não é um numero real (as frações são desconsideradas aqui).\nVerifique o valor informado e tente novamente!\n\n");
			return 0;
		}
	} else if (dado->type == 'c') {
		if (strlen(dado->value) != 1) {
			printf("O valor informado não é um caractere único.\nPor tente novamente!\n\n");
			return 0;
		} else {
			if (!isalnum(dado->value)) {
				printf("Os caracteres aceitos são apenas digitos de 0 a 9 e letras (maiusculas ou minusculas) de A a Z.\nPor favor verifique o valor informado e tente novamente!\n\n");
				return 0;
			}
		}
	} else if (dado->type == 't') {
		for (i = 0; i < strlen(dado->value) - 1; i++) {
			if (!(isalnum(dado->value))) {
				printf("O caracteres aceitos são apenas digitos de 0 a 9 e letras (maiusculas ou minusculas) de A a Z.\nPor favor verifique o valor informado e tente novamente!\n\n");
				return 0;
			}
	 	}
	} else {
		printf("Tipo inválido, tente novamente!\n\n");
		return 0;
	}
	return 1;
}

int inserirLinha(table *tabela) {
	FILE *arquivo;
	string nomeArquivo;
	nomeArquivo = malloc(sizeof(char) * 53);
	strcpy(nomeArquivo, tabela->name);
	strcat(nomeArquivo, ".tb");
	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir tabela!\n");
		fclose(arquivo);
		free(nomeArquivo);
		return 0;
	} else {
		date dado;
		line tupla;
		FILE *arquivoTemp;
		int i, c = 1, qtdLinhas;
		arquivoTemp = fopen("arqTmp.txt", "w+");
		fscanf(arquivo, "%u colunas, %d linhas preencidas\n", &tabela->numOfAtts, &qtdLinhas);
		fprintf(arquivoTemp, "%u colunas, %d linhas preencidas\n", tabela->numOfAtts, ++qtdLinhas);
		tabela->primaryKeyName = malloc(sizeof(char) * 50);
		tabela->attributesName = malloc(sizeof(char) * --tabela->numOfAtts);
		for (i = 0; i < tabela->numOfAtts; i++)
			tabela->attributesName[i] = malloc(sizeof(char) * 50);
		tabela->attributesType = malloc(sizeof(char) * tabela->numOfAtts);
		fscanf(arquivo, "%s\t-\t", tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fscanf(arquivo, "%s (%c)\t-\t", tabela->attributesName[i], &tabela->attributesType[i]);
		fscanf(arquivo, "%s (%c)\n", tabela->attributesName[i], &tabela->attributesType[i]);
		fprintf(arquivoTemp, "%s\t-\t", tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivoTemp, "%s (%c)\t-\t", tabela->attributesName[i], tabela->attributesType[i]);
		fprintf(arquivoTemp, "%s (%c)\n", tabela->attributesName[i], tabela->attributesType[i]);
		tupla.attributes = malloc(sizeof(char) * tabela->numOfAtts);
		for (i = 0; i < tabela->numOfAtts; i++)
			tupla.attributes[i] = malloc(sizeof(char) * 50);
		while (--qtdLinhas) {
			fscanf(arquivo, "%u\t-\t", &tupla.primaryKeyValue);
			fprintf(arquivoTemp, "%u\t-\t", tupla.primaryKeyValue);
			for (i = 0; i < tabela->numOfAtts - 1; i++) {
				fscanf(arquivo, "%s\t-\t", tupla.attributes[i]);
				fprintf(arquivoTemp, "%s\t-\t", tupla.attributes[i]);
			}
			fscanf(arquivo, "%s\n", tupla.attributes[i]);
			fprintf(arquivoTemp, "%s\n", tupla.attributes[i]);
		}
		fclose(arquivo);
		dado.value = malloc(sizeof(char) * 50);
		printf("Informe os dados da nova linha!\n");
		while (c) {
			printf("%s: ", tabela->primaryKeyName);
			scanf("%s", dado.value);
			dado.type = 'p';
			if (validarDado(&dado)) {
				tupla.primaryKeyValue = (unsigned int) atoi(dado.value);
				c = 0;
			}
		}
		for (i = 0; i < tabela->numOfAtts; i++) {
			//printf("%s:\t", tabela->attributesName[i]);
			//scanf("%s", tupla.attributes[i]);
			c = 1;
			while (c) {
				printf("%s: ", tabela->attributesName[i]);
				scanf("%s", dado.value);
				dado.type = tabela->attributesType[i];
				if (validarDado(&dado)) {
					strcpy(tupla.attributes[i], dado.value);
					c = 0;
				}
			}
		}
		free(dado.value);
		fprintf(arquivoTemp, "%u\t-\t", tupla.primaryKeyValue);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivoTemp, "%s\t-\t", tupla.attributes[i]);
		fprintf(arquivoTemp, "%s\n", tupla.attributes[tabela->numOfAtts - 1]);
		fclose(arquivoTemp);
		remove(nomeArquivo);
		rename("arqTmp.txt", nomeArquivo);
		free(nomeArquivo);
		free(tupla.attributes);
		free(tabela->attributesName);
		free(tabela->primaryKeyName);
		return 1;
	}
}

int criarBanco(database *banco) {
	FILE *arquivo;
	string nomeArquivo;
	arquivo = fopen("sgbd-itp.db", "r");
	if (arquivo == NULL) {
		arquivo = fopen("sgbd-itp.db", "w+");
		fprintf(arquivo, "%d bancos\n", 1);
		fprintf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", banco->name, banco->numOfTabs, banco->usrRoot, banco->pswRoot);
		fclose(arquivo);
		nomeArquivo = malloc(sizeof(char) * 53);
		strcpy(nomeArquivo, banco->name);
		strcat(nomeArquivo, ".db");
		arquivo = fopen(nomeArquivo, "w+");
		fprintf(arquivo, "%d tabelas\n", 0);
		free(nomeArquivo);
		fclose(arquivo);
		return 1;
	} else {
		int qtdBancos;
		FILE *arquivoTemp;
		database bancoTemp;
		arquivoTemp = fopen("arqTmp.txt", "w+");
		fscanf(arquivo, "%d bancos\n", &qtdBancos);
		fprintf(arquivoTemp, "%d bancos\n", ++qtdBancos);
		bancoTemp.name = malloc(sizeof(char) * 50);
		bancoTemp.usrRoot = malloc(sizeof(char) * 10);
		bancoTemp.pswRoot = malloc(sizeof(char) * 18);
		while (--qtdBancos) {
			fscanf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, &bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
			fprintf(arquivoTemp, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
		}
		free(bancoTemp.name);
		free(bancoTemp.usrRoot);
		free(bancoTemp.pswRoot);
		fprintf(arquivoTemp, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", banco->name, banco->numOfTabs, banco->usrRoot, banco->pswRoot);
		fclose(arquivo);
		fclose(arquivoTemp);
		remove("sgbd-itp.db");
		rename("arqTmp.txt", "sgbd-itp.db");
		nomeArquivo = malloc(sizeof(char) * 53);
		strcpy(nomeArquivo, banco->name);
		strcat(nomeArquivo, ".db");
		arquivo = fopen(nomeArquivo, "w+");
		fprintf(arquivo, "%d tabelas\n", 0);
		free(nomeArquivo);
		fclose(arquivo);
		return 1;
	}
}

int autenticar(database *banco) {
	FILE *arquivo;
	arquivo = fopen("sgbd-itp.db", "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir o banco de dados central!\n\n");
		fclose(arquivo);
		return 0;
	} else {
		int qtdBancos;
		fscanf(arquivo, "%d bancos\n", &qtdBancos);
		if (qtdBancos == 0) {
			printf("Atualmente não existem bancos de dados criados!\n\n");
			fclose(arquivo);
			return 0;
		} else {
			database bancoTemp;
			bancoTemp.name = malloc(sizeof(char) * 50);
			bancoTemp.usrRoot = malloc(sizeof(char) * 10);
			bancoTemp.pswRoot = malloc(sizeof(char) * 18);
			while (qtdBancos--) {
				fscanf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, &bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
				if (strcmp(bancoTemp.name, banco->name) || strcmp(bancoTemp.usrRoot, banco->usrRoot) || strcmp(bancoTemp.pswRoot, banco->pswRoot))
					continue;
				else {
					printf("Autorizado!\n\n");
					fclose(arquivo);
					free(bancoTemp.name);
					free(bancoTemp.usrRoot);
					free(bancoTemp.pswRoot);
					return 1;
				}
			}
			fclose(arquivo);
			free(bancoTemp.name);
			free(bancoTemp.usrRoot);
			free(bancoTemp.pswRoot);
			printf("Dados incorretos. Teste novamente!\n");
			return 0;
		}
	}
}

int deletarTabela(database *banco, table *tabela) {
	FILE *arquivo;
	string nomeBanco;
	nomeBanco = malloc(sizeof(char) * 53);
	nomeBanco = banco->name;
	strcat(nomeBanco, ".db");
	arquivo = fopen(nomeBanco, "r");
	if (arquivo == NULL)
		return 0;
	else {
		int i, qtdTabelas;
		FILE *arquivoTemp;
		table tabelaTemp;
		string nomeArqDel;
		arquivoTemp = fopen("arqTmp.txt", "w+");
		fscanf(arquivo, "%d tabelas\n", &qtdTabelas);
		fprintf(arquivoTemp, "%d tabelas\n", qtdTabelas - 1);
		tabelaTemp.name = malloc(sizeof(char) * 50);
		tabelaTemp.primaryKeyName = malloc(sizeof(char) * 50);
		while (qtdTabelas--) {
			fscanf(arquivo, "%s\t-\t%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", tabelaTemp.name, &tabelaTemp.numOfAtts, tabelaTemp.primaryKeyName);
			tabela->attributesName = malloc(sizeof(char) * tabelaTemp.numOfAtts);
			for (i = 0; i < tabelaTemp.numOfAtts; i++)
				tabela->attributesName[i] = malloc(sizeof(char) * 50);
			for (i = 0; i < tabelaTemp.numOfAtts - 1; i++)
				fscanf(arquivo, "%s, ", tabela->attributesName[i]);
			fscanf(arquivo, "%s\n", tabela->attributesName[tabelaTemp.numOfAtts - 1]);
			if (strcmp(tabelaTemp.name, banco->name))
				fprintf(arquivoTemp, "%s\t-\t%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", tabelaTemp.name, tabelaTemp.numOfAtts, tabelaTemp.primaryKeyName);
			free(tabela->attributesName);
		}
		free(tabelaTemp.name);
		free(tabelaTemp.primaryKeyName);
		fclose(arquivo);
		fclose(arquivoTemp);
		remove(nomeBanco);
		rename("arqTmp.txt", nomeBanco);
		nomeArqDel = malloc(sizeof(char) * 53);
		strcpy(nomeArqDel, tabela->name);
		strcat(nomeArqDel, ".tb");
		remove(nomeArqDel);
		free(nomeArqDel);
		
		//comando = malloc(sizeof(char) * 59);
		//comando = "rm -f ";
		//strcat(comando, tabela->name);
		//strcat(comando, ".tb");
		//system(comando);
		//free(comando);

		return 1;
	}
}

int deletarBanco(database *banco) {
	FILE *arquivo;
	arquivo = fopen("sgbd-itp.db", "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir banco de dados central!\n\n");
		return 0;
	} else {
		int qtdBancos;
		fscanf(arquivo, "%d bancos\n", &qtdBancos);
		if (qtdBancos == 0) {
			printf("Não existem bancos de dados para serem excluidos!\n\n");
			return 0;
		} else {
			string nomeArqDel;
			FILE *arquivoTemp;
			database bancoTemp;
			arquivoTemp = fopen("arqTmp.txt", "w+");
			fprintf(arquivoTemp, "%d bancos\n", qtdBancos - 1);
			bancoTemp.name = malloc(sizeof(char) * 50);
			bancoTemp.usrRoot = malloc(sizeof(char) * 10);
			bancoTemp.pswRoot = malloc(sizeof(char) * 18);
			while (qtdBancos--) {
				fscanf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, &bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
				if (strcmp(bancoTemp.name, banco->name))
					fprintf(arquivoTemp, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
			}
			free(bancoTemp.name);
			free(bancoTemp.usrRoot);
			free(bancoTemp.pswRoot);
			fclose(arquivo);
			fclose(arquivoTemp);
			remove("sgbd-itp.db");
			rename("arqTmp.txt", "sgbd-itp.db");
			nomeArqDel = malloc(sizeof(char) * 53);
			strcpy(nomeArqDel, banco->name);
			strcat(nomeArqDel, ".db");
			remove(nomeArqDel);
			free(nomeArqDel);

			//comando = malloc(sizeof(char) * 59);
			//comando = "rm -f ";
			//strcat(comando, tabela->name);
			//strcat(comando, ".tb");
			//system(comando);
			//free(comando);

			return 1;
		}
	}
}

int deletarLinha(table *tabela) {
	FILE *arquivo;
	string nomeTabela;
	nomeTabela = malloc(sizeof(char) * 53);
	strcpy(nomeTabela, tabela->name);
	strcat(nomeTabela, ".tb");
	arquivo = fopen(nomeTabela, "r");
	if (arquivo == NULL)
		return 0;
	else {
		date chavePrimaria;
		unsigned int linhaDel = 0, c = 3;
		chavePrimaria.value = malloc(sizeof(char) * 50);
		while (c--) {
			printf("Informe a chave primaria da linha que deseja excluir:\t");
			scanf("%s", chavePrimaria.value);
			chavePrimaria.type = 'p';
			if (validarDado(&chavePrimaria)) {
				linhaDel = (unsigned int) atoi(chavePrimaria.value);
				c = 0;
			} else
				continue;
		}
		free(chavePrimaria.value);
		if (linhaDel != 0) {
			line linhaTemp;
			int i, qtdLinhas;
			FILE *arquivoTemp;
			arquivoTemp = fopen("arqTmp.txt", "w+");
			tabela->primaryKeyName = malloc(sizeof(char) * 50);
			fscanf(arquivo, "%u colunas, %d linhas preencidas\n", &tabela->numOfAtts, &qtdLinhas);
			fprintf(arquivoTemp, "%u colunas, %d linhas preencidas\n%s\t-\t", tabela->numOfAtts, qtdLinhas - 1, tabela->primaryKeyName);
			tabela->attributesName = malloc(sizeof(char) * --tabela->numOfAtts);
			tabela->attributesType = malloc(sizeof(char) * tabela->numOfAtts);
			for (i = 0; i < tabela->numOfAtts; i++)
				tabela->attributesName[i] = malloc(sizeof(char) * 50);
			for (i = 0; i < tabela->numOfAtts - 1; i++)
				fscanf(arquivo, "%s (%c)\t-\t", tabela->attributesName[i], &tabela->attributesType[i]);
			fscanf(arquivo, "%s (%c)\n", tabela->attributesName[i], &tabela->attributesType[i]);
			fprintf(arquivoTemp, "%s\t-\t", tabela->primaryKeyName);
			for (i = 0; i < tabela->numOfAtts - 1; i++)
				fprintf(arquivoTemp, "%s (%c)\t-\t", tabela->attributesName[i], tabela->attributesType[i]);
			fprintf(arquivoTemp, "%s (%c)\n", tabela->attributesName[i], tabela->attributesType[i]);
			free(tabela->attributesName);
			free(tabela->attributesType);
			while (qtdLinhas--) {
				fscanf(arquivo, "%u\t-\t", &linhaTemp.primaryKeyValue);
				fprintf(arquivoTemp, "%u\t-\t", linhaTemp.primaryKeyValue);
				linhaTemp.attributes = malloc(sizeof(char) * tabela->numOfAtts);
				for (i = 0; i < tabela->numOfAtts; i++)
					linhaTemp.attributes[i] = malloc(sizeof(char) * 50);
				for (i = 0; i < tabela->numOfAtts - 1; i++)
					fscanf(arquivo, "%s\t-\t", linhaTemp.attributes[i]);
				fscanf(arquivo, "%s\n", linhaTemp.attributes[tabela->numOfAtts - 1]);
				if (linhaTemp.primaryKeyValue == linhaDel)
					continue;
				else {
					fprintf(arquivoTemp, "%u\t-\t", linhaTemp.primaryKeyValue);
					for (i = 0; i < tabela->numOfAtts - 1; i++)
						fprintf(arquivoTemp, "%s\t-\t", linhaTemp.attributes[i]);
					fprintf(arquivoTemp, "%s\n", linhaTemp.attributes[tabela->numOfAtts - 1]);
				}
				free(linhaTemp.attributes);
			}
			fclose(arquivo);
			fclose(arquivoTemp);
			remove(nomeTabela);
			rename("arqTmp.txt", nomeTabela);
			return 1;
		} else
			return 0;
	}
}

int criarTabela(table *tabela, database *banco) {
	FILE *arquivo;
	string nomeArquivo;
	nomeArquivo = malloc(sizeof(char) * 53);
	strcpy(nomeArquivo, banco->name);
	strcat(nomeArquivo, ".db");
	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		free(nomeArquivo);
		fclose(arquivo);
		return 0;
	} else {
		int i, c;
		table tabelaTemp;
		FILE *arquivoTemp;
		database bancoTemp;
		arquivoTemp = fopen("arqTmp.txt", "w+");
		fscanf(arquivo, "%u tabelas\n", &banco->numOfTabs);
		c = banco->numOfTabs + 1;
		fprintf(arquivoTemp, "%u tabelas\n", c);
		tabelaTemp.name = malloc(sizeof(char) * 50);
		tabelaTemp.primaryKeyName = malloc(sizeof(char) * 50);
		while (--c) {
			fscanf(arquivo, "%s\t-\t%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", tabelaTemp.name, &tabelaTemp.numOfAtts, tabelaTemp.primaryKeyName);
			tabelaTemp.attributesName = malloc(sizeof(char) * tabelaTemp.numOfAtts);
			for (i = 0; i < tabelaTemp.numOfAtts; i++)
				tabelaTemp.attributesName[i] = malloc(sizeof(char) * 50);
			tabelaTemp.attributesType = malloc(sizeof(char) * tabelaTemp.numOfAtts);
			for (i = 0; i < tabelaTemp.numOfAtts - 1; i++)
				fscanf(arquivo, "%s (%c), ", tabelaTemp.attributesName[i], &tabelaTemp.attributesType[i]);
			fscanf(arquivo, "%s (%c)\n", tabelaTemp.attributesName[i], &tabelaTemp.attributesType[i]);
			fprintf(arquivoTemp, "%s\t-\t%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", tabelaTemp.name, tabelaTemp.numOfAtts, tabelaTemp.primaryKeyName);
			for (i = 0; i < tabelaTemp.numOfAtts - 1; i++)
				fprintf(arquivoTemp, "%s (%c), ", tabelaTemp.attributesName[i], tabelaTemp.attributesType[i]);
			fprintf(arquivoTemp, "%s (%c)\n", tabelaTemp.attributesName[i], tabelaTemp.attributesType[i]);
			free(tabelaTemp.attributesName);
			free(tabelaTemp.attributesType);
		}
		fclose(arquivo);
		free(tabelaTemp.name);
		free(tabelaTemp.primaryKeyName);
		fprintf(arquivoTemp, "%s\t-\t%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", tabela->name, tabela->numOfAtts, tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivoTemp, "%s (%c), ", tabela->attributesName[i], tabela->attributesType[i]);
		fprintf(arquivoTemp, "%s (%c)\n", tabela->attributesName[i], tabela->attributesType[i]);
		fclose(arquivoTemp);
		remove(nomeArquivo);
		rename("arqTmp.txt", nomeArquivo);
		free(nomeArquivo);
		arquivo = fopen("sgbd-itp.db", "r");
		arquivoTemp = fopen("arqTmp.txt", "w+");
		fscanf(arquivo, "%d bancos\n", &c);
		fprintf(arquivoTemp, "%d bancos\n", c);
		bancoTemp.name = malloc(sizeof(char) * 50);
		bancoTemp.usrRoot = malloc(sizeof(char) * 10);
		bancoTemp.pswRoot = malloc(sizeof(char) * 18);
		while (c--) {
			fscanf(arquivo, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, &bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
			if (strcmp(bancoTemp.name, banco->name))
				fprintf(arquivoTemp, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, bancoTemp.numOfTabs, bancoTemp.usrRoot, bancoTemp.pswRoot);
			else
				fprintf(arquivoTemp, "%s\t-\t%u tabelas\t-\tUsuário Admin: %s\t-\tSenha do Usuário Admin: %s\n", bancoTemp.name, bancoTemp.numOfTabs + 1, bancoTemp.usrRoot, bancoTemp.pswRoot);
		}
		free(bancoTemp.name);
		free(bancoTemp.usrRoot);
		free(bancoTemp.pswRoot);
		fclose(arquivo);
		fclose(arquivoTemp);
		remove("sgbd-itp.db");
		rename("arqTmp.txt", "sgbd-itp.db");
		nomeArquivo = malloc(sizeof(char) * 53);
		strcpy(nomeArquivo, tabela->name);
		strcat(nomeArquivo, ".tb");
		arquivo = fopen(nomeArquivo, "w+");
		fprintf(arquivo, "%u colunas, %u linhas preencidas\n%s\t-\t", tabela->numOfAtts + 1, 0, tabela->primaryKeyName);
		for (i = 0; i < tabela->numOfAtts - 1; i++)
			fprintf(arquivo, "%s (%c)\t-\t", tabela->attributesName[i], tabela->attributesType[i]);
		 fprintf(arquivo, "%s (%c)\n", tabela->attributesName[tabela->numOfAtts - 1], tabela->attributesType[tabela->numOfAtts - 1]);
		free(nomeArquivo);
		fclose(arquivo);
		return 1;
	}
}

int verificarTabela(table *tabela, database *banco) {
	//FILE *arquivo;
	//string nomeArquivo;
	//nomeArquivo = malloc(sizeof(char) * 53);
	//strcpy(nomeArquivo, banco->name);
	//strcat(nomeArquivo, ".db");
	//arquivo = fopen(nomeArquivo, "r");
	//if (arquivo == NULL) {
	//	printf("Erro ao abrir banco de dados, verifique os valores informados e tente novamente!\n\n");
	//	fclose(arquivo);
	//	return 0;
	//} else {
	//	fscanf(arquivo, "%u tabelas\n", &banco->numOfTabs);
	//	int i;
	//	table tabelaTemp;
	//	tabelaTemp.name = malloc(sizeof(char) * 50);
	//	tabelaTemp.primaryKeyName = malloc(sizeof(char) * 50);
	//	while (banco->numOfTabs--) {
	//		fscanf(arquivo, "%s\t-\t", tabelaTemp.name);
	//		if (strcmp(tabelaTemp.name, tabela->name)) {
	//			fscanf(arquivo, "%u colunas\t-\tChave Primaria: %s\t-\tColunas: ", &tabelaTemp.numOfAtts, tabelaTemp.primaryKeyName);
	//			tabela->attributesName = malloc(sizeof(char) * tabelaTemp.numOfAtts);
	//			for (i = 0; i < tabelaTemp.numOfAtts; i++)
	//				tabela->attributesName[i] = malloc(sizeof(char) * 50);
	//			for (i = 0; i < tabelaTemp.numOfAtts - 1; i++)
	//				fscanf(arquivo, "%s, ", tabela->attributesName[i]);
	//			fscanf(arquivo, "%s\n", tabela->attributesName[tabelaTemp.numOfAtts - 1]);
	//			free(tabela->attributesName);
	//		} else {
	//			printf("Já existe uma tabela com esse nome!\n\n");
	//			fclose(arquivo);
	//			free(tabelaTemp.name);
	//			free(tabelaTemp.primaryKeyName);
	//			return 0;
	//		}
	//	}
	//	fclose(arquivo);
	//	free(nomeArquivo);
	//	free(tabelaTemp.name);
	//	free(tabelaTemp.primaryKeyName);
	//	return 1;
	//}
	return 1;
}

int compararDados(char tipoComp, date *primeiroDado, date *segundoDado) {
	if (primeiroDado->type == 'r' || primeiroDado->type == 'i') {
		double valorPrimeiroDado, valorSegundoDado;
		valorPrimeiroDado = atof(primeiroDado->value);
		valorSegundoDado = atof(segundoDado->value);
		if (tipoComp == '1' && valorPrimeiroDado && valorSegundoDado) {
			//if ()
		} else if (tipoComp == '2' && valorPrimeiroDado && valorSegundoDado) {

		} else if (tipoComp == '4' && valorPrimeiroDado && valorSegundoDado) {

		} else if (tipoComp == '5' && valorPrimeiroDado && valorSegundoDado) {

		} else {
			printf("Essa comparação não é válida para o tipo de dado informado!\n\n");
			return 0;
		}
	}
	return 1;
}
