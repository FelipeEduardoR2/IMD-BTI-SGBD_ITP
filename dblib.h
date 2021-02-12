#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//t; s;
#define t printf("Teste!\n");
#define s exit(EXIT_SUCCESS);
typedef char* string;
typedef char** vetorString;
typedef struct tabela {
	unsigned int numOfAtts;
	vetorString attributesName;
	string name, primaryKeyName, attributesType;
} table;
typedef struct linhaTabela {
	vetorString attributes;
	unsigned int primaryKeyValue;
} line;
typedef struct bancoDeDados {
	unsigned int numOfTabs;
	string name, usrRoot, pswRoot;
} database;
typedef struct dadosTabela {
	char type;
	string value;
} date;
void listarBancos();
void exibirTabela(table *tabela);
void listarTabelas(database *banco);
void pesquisarNaTabela(table *tabela);
int validarDado(date *dado);
int inserirLinha(table *tabela);
int criarBanco(database *banco);
int autenticar(database *banco);
int deletarTabela(database *banco, table *tabela);
int deletarBanco(database *banco);
int deletarLinha(table *tabela);
int criarTabela(table *tabela, database *banco);
int verificarTabela(table *tabela, database *banco);
int compararDados(char tipoComp, date *primeiroDado, date *segundoDado);
