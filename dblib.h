typedef struct tabela {
	unsigned int numOfAtts; 
	char *name, **attributes, *primaryKeyName;
} table;
typedef struct linhaTabela {
	unsigned int primaryKeyValue; 
	char **attributes;
} line;
typedef struct bancoDeDados {
	unsigned int numOfTabs;
	char *name, *usrRoot, *pswRoot;
} database;
void listarBancos();
void exibirTabela(table *tabela);
void listarTabelas(database *banco);
//void pesquisarNaTabela(table *tabela); Função ainda não implementada
int criarBanco(database *banco);
int autenticar(database *banco);  //Função ainda não implementada
int deletarTabela(table *tabela); //Função ainda não implementada
int deletarBanco(database *banco);
int inserirLinha(line *tupla, table *tabela);
int deletarLinha(line *tupla, table *tabela); //Função ainda não implementada
int criarTabela(table *tabela, database *banco);
int verificarTabela(table *tabela, database *banco);
