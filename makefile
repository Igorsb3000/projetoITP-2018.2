# My first makefile

all: kiexe

kiexe: main.o funcoes_tab.o
	gcc -o kiexe main.o funcoes_tab.o

main.o: main.c lista_func.h
	gcc -o main.o main.c -c -W -Wall -pedantic

funcoes_tab.o: funcoes_tab.c lista_func.h
	gcc -o funcoes_tab.o funcoes_tab.c -c -W -Wall -pedantic

clean:
	rm  *.o *~ kiexe
