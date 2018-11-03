#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tabela_t{
  unsigned int id;
  char nome[50];
  int L, C;
  char ***tab;
}tabela;
//comentário

int main(void) {
  FILE *tabela_file;
  tabela tabela_user;
  int i,j;
  unsigned int chave_itens;
  char nome_campo[50], tipo_campo[50];

  // criando tabela
  printf("Digite o nome da tabela: ");
  scanf("%s", tabela_user.nome);
  strcat(tabela_user.nome,".tab");
  tabela_file = fopen(tabela_user.nome, "wr+"); 

  printf("Quantos campos e quantos itens irá inserir? (c l)\n");
  scanf("%d %d", &tabela_user.C, &tabela_user.L); 

  tabela_user.tab=malloc(sizeof(char**)*tabela_user.L); //linhas alocadas
  for(int i=0; i<tabela_user.L; i++){
    tabela_user.tab[i]=malloc(sizeof(char*)*tabela_user.C); //colunas alocadas
  }
  for(int i=0; i<tabela_user.L; i++){
    for(int j=0; j<tabela_user.C; j++){
      tabela_user.tab[i][j]=malloc(sizeof(char)*50); // strings alocadas
    }
  }
  
  j=0;
  do{
    printf("Inserira o campo[%d] e o seu tipo:\n", j+1);
    scanf(" %s %s", nome_campo, tipo_campo); // precisa guardar o tipo em algum lugar !!!!!!!!!!!!!!!!!!!!!!!!!!

    if(strcmp(tipo_campo,"int")!=0 && strcmp(tipo_campo,"float")!=0 && strcmp(tipo_campo,"double")!=0 && strcmp(tipo_campo,"char")!=0 && strcmp(tipo_campo,"string")!=0){
      printf("ERRO: Os tipos precisam ser: int, float, double, char ou string.\n");
    } else{
      strcpy(tabela_user.tab[0][j],nome_campo);
      fprintf(tabela_file,"%*s",15,tabela_user.tab[0][j]); //*=garante distância mínima
      j++;
    }
		
  }while(j<tabela_user.C);
  fprintf(tabela_file,"\n");
  
  /*
  printf("Qual dos campos é o ID da tabela:\n");
  scanf("%s",&nome_campo);
  do{
    for(i=0;i<;i++){
      if()
	printf("ID invalido. O ID da tabela precisa conter inteiros positivos (tipo int).\n");
	  invalido=0;
	break;
    }
  }while();
  */
  //strcpy(tabela_user.id,nome_campo);
  //verifique se o id da tabela é valido


	
	
  if(tabela_file == NULL){
    printf("Tabela não abriu!\n");
  }
  else{
    fclose(tabela_file);
  }

  // fazer o free de tabela_user.tab
  return 0;
}
