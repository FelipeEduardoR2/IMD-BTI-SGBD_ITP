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
void pesquisarNaTabela(table *tabela);
int criarBanco(database *banco);
int autenticar(database *banco);
int deletarTabela(table *tabela);
int deletarBanco(database *banco);
int inserirLinha(line *tupla, table *tabela);
int deletarLinha(line *tupla, table *tabela);
int criarTabela(table *tabela, database *banco);
int verificarTabela(table *tabela, database *banco);
