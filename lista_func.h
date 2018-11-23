#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // macros dos limites dos tipos int, uint, char, entre outra

enum tipos_tab{int_=1, float_, double_, char_, string_};

typedef struct tabela_t{
  char nome[50];
  int C;
  char **tab_L; // linha da tabela
  enum tipos_tab *tipos; //char **tab_tipos; // tipos de cada campo da tabela
}tabela;

tabela *alocaStruct_tab(int col);

void fillStruct_tab(tabela *tab, char nome_tab[50], int col);

void freeStruct_tab(tabela *tab);

void conversao_tipos(enum tipos_tab TIPO, char str_tipo[10]);

int checaLimite_campos(char campo[50], enum tipos_tab tipo_campo);

void listagem_tab();

void cria_tab();

void insereLinha_tab(char nome_tab[50], int n);

void editar_tab(char nome_tab[50], int n);

void insereColuna_tab(char nome_tab[50], int n);

void listarDados_tab(char nome_tab[50], int n);

int pesquisarDados_tab(char nome_tab[50], int n);

void apagarLinha(char nome_tab[50], int n);

void apagarTab(char nome_tab[50], int n);



