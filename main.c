#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tabela_t{
  unsigned int id;
  char nome[50];
  int C;
  char **tab_L; // linha da tabela
  char **tab_tipos; // tipos de cada campo da tabela
}tabela;


int main(void) {
  FILE *tabela_file;
  tabela tabela_user;
  int i,j;
  char nome_campo[50], tipo_campo[50]; // auxiliares
  int campoOK, idOK; // bool

  // criando tabela
  printf("Digite o nome da tabela: ");
  scanf("%s", tabela_user.nome);
  strcat(tabela_user.nome,".tab");
  tabela_file = fopen(tabela_user.nome, "wr+"); 

  printf("Quantos campos irá inserir?\n");
  scanf("%d", &tabela_user.C); 

  //alocando vetores da struct
  tabela_user.tab_L=malloc(sizeof(char*)*tabela_user.C); //colunas alocadas
  for(int j=0; j<tabela_user.C; j++)
    tabela_user.tab_L[j]=malloc(sizeof(char)*50); // strings alocadas
  
  tabela_user.tab_tipos=malloc(sizeof(char*)*tabela_user.C); //colunas alocadas
  for(int j=0; j<tabela_user.C; j++)
    tabela_user.tab_tipos[j]=malloc(sizeof(char)*10); // strings alocadas
  

  j=0;
  do{
    printf("Insira o campo[%d] e o seu tipo:\n", j+1);
    scanf(" %s %s", nome_campo, tipo_campo); 

    // verifique que os campos inseridos são únicos		
    campoOK=1;
    for(int i=0; i<j; i++){
      if(strcmp(tabela_user.tab_L[i],nome_campo)==0){
	campoOK=0;
	break;
      }
    }

    if(strcmp(tipo_campo,"int")!=0 && strcmp(tipo_campo,"float")!=0 && strcmp(tipo_campo,"double")!=0 && strcmp(tipo_campo,"char")!=0 && strcmp(tipo_campo,"string")!=0){
      printf("ERRO: Os tipos precisam ser: int, float, double, char ou string.\n");
    } else if(!campoOK){ 
      printf("Campo já foi criado.\n"); // mensagem de erro caso campo inserido já exista
    }else{      
	strcpy(tabela_user.tab_L[j],nome_campo);
	strcpy(tabela_user.tab_tipos[j],tipo_campo);
	j++;
    }

  }while(j<tabela_user.C);

  // Criando campo de id
  int j_id;
  do{
    idOK=0;
    do{
      campoOK=0;
      printf("Qual dos campos é o ID da tabela? \n");
      scanf("%s",nome_campo);
  
      // verificar se campo ID passado existe
      for(int j=0; j<tabela_user.C; j++){
	if(strcmp(tabela_user.tab_L[j],nome_campo)==0){
	  campoOK=1;
	  j_id=j;
	  break;
	}
      }

      if(!campoOK){
	printf("Campo inexistente. \nOs campos passados são: \n");
	for(int j=0; j<tabela_user.C; j++)
	  printf("%s ",tabela_user.tab_L[j]);
	printf("\n");
      }
    }while(!campoOK);
  
    // verifique se o id da tabela é valido
    if(strcmp(tabela_user.tab_tipos[j_id],"int")==0){
      idOK=1;
    } else{ 
      printf("ID invalido. O ID da tabela precisa conter inteiros positivos (tipo int).\n");
    }
  
  }while(!idOK);

  // guarde na tabela a linha de tipo
  fprintf(tabela_file,"%s \t",tabela_user.tab_tipos[j_id]); // tipo do id
  for(int j=0; j<tabela_user.C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%s \t",tabela_user.tab_tipos[j]);
  }
  fprintf(tabela_file,"\n");	

  // guarde na tabela a linha de campos
  fprintf(tabela_file,"%s \t",tabela_user.tab_L[j_id]); // campo do id	
  for(int j=0; j<tabela_user.C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%s \t",tabela_user.tab_L[j]);	
  }
  fprintf(tabela_file,"\n");	

  if(tabela_file == NULL){
    printf("Tabela não abriu!\n");
  }
  else{
    fclose(tabela_file);
  }

  

  // fazer o free de tabela_user.tab
  return 0;
}
