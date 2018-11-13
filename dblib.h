typedef struct tabela {
	unsigned int numOfAtt;
	char *name, **attributes, *primaryKeyName; //,*usrAdmin, *foreingKey; Ambas informações ainda serão utilizadas.
} table;
int criarTabela(char *nomeDaTabela, char *nomeDoBanco, int qtdAtributos);
void listarTabelas(char *nomeDoBanco);
//int verificarTabela(char *tabela, char *banco); Função ainda por ser implementada.
