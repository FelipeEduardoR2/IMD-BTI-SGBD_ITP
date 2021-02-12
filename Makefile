######Geral######
########Limpeza de arquivos objeto
cleanObjs:
	rm -rf *.o

########Limpeza de arquivos residuais
cleanAll:
	make cleanObjs
	rm -rf sgbd-run

######Criação de objetos######
lib: dblib.c dblib.h
	gcc -o dblib.o -c dblib.c

main: main-db.c dblib.h
	gcc -o main-db.o -c main-db.c

makeObjs:
	make main
	make lib

######Executável######
run: sgbd-run
	./sgbd-run

runSGBD: dblib.o main.o
	make makeObjs
	gcc -o sgbd-run -c main.o dblib.o

runAll:
	make runSGBD
	make run
	make cleanObjs
	
all:
	make runAll
