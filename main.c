#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
enum tipos_tab{ int_=1, float_, double_, char_, string_};


typedef struct tabela_t{
  char nome[50];
  int C;
  char **tab_L; // linha da tabela
  enum tipos_tab *tipos; //char **tab_tipos; // tipos de cada campo da tabela
}tabela;

void conversao_tipos(enum tipos_tab TIPO, char str_tipo[10]){
   /*switch(TIPO){
	case(1)
           strcpy(str_tipo,"int");
	   break;
	case(2)
           strcpy(str_tipo, "float");
	   break;
	case(3)
           strcpy(str_tipo,"double");
           break;
	case(4)
           strcpy(str_tipo, "char");
           break;
	case(5)
           strcpy(str_tipo,"string");
	   break;
	default:
	   printf("Tipo inválido!\n");
	   break;

  }
	*/
     char tipos_all[][10]={"int", "float", "double", "char", "string"};
     strcpy(str_tipo, tipos_all[TIPO-1]);

}

//Função para listar todas tabelas
void listagem_tab(){ 
  FILE *relacao_file;
  char nome[50];
  int n;


  printf("Tabelas existentes:\n");

  relacao_file = fopen("relacaoTab", "r");

  while(fscanf(relacao_file,"%s %*d\n",nome)!=EOF){ //enquanto não for End of File, continue imprimindo
    printf("%s\n",nome);
  }

  if(relacao_file == NULL){
    printf("Relação de tabelas não existe!\n");
  }
  else{
    fclose(relacao_file);
  }

}

//Função para criar uma nova tabela
void cria_tab(){
  FILE *tabela_file, *relacao_file;
  tabela tabela_user;
  int i,j;
  char nome_campo[50];
  int tipo_campo; 
  int campoOK, idOK; // bool

  printf("Digite o nome da tabela: "); //printf("%d", __LINE__);
  scanf("%s", tabela_user.nome);
  strcat(tabela_user.nome,".tab");
  tabela_file = fopen(tabela_user.nome, "wr+"); 

  printf("Quantos campos irá inserir?\n");
  scanf("%d", &tabela_user.C); 

  //alocando vetores da struct
  tabela_user.tab_L=malloc(sizeof(char*)*tabela_user.C); //colunas alocadas
  for(int j=0; j<tabela_user.C; j++)
    tabela_user.tab_L[j]=malloc(sizeof(char)*50); // strings alocadas
  
  tabela_user.tipos=malloc(sizeof(enum tipos_tab)*tabela_user.C); //vetor de enum alocado

  j=0;
  do{
    tipo_campo=0;
    printf("\nInsira o campo[%d](sem espaços) e o seu tipo\n\n 1-int\n 3-float\n 3-double\n 4-char\n 5-string\n\n", j+1);
    scanf(" %s %d", nome_campo, &tipo_campo); 

    // verifique que os campos inseridos são únicos		
    campoOK=1;
    for(int i=0; i<j; i++){
      if(strcmp(tabela_user.tab_L[i],nome_campo)==0){
	campoOK=0;
	break;
      }
    }
	
    if(tipo_campo != 1 && tipo_campo != 2 && tipo_campo != 3 && tipo_campo != 4 && tipo_campo != 5){
      printf("ERRO: Os tipos precisam ser: 1-int, 2-float, 3-double, 4-char ou 5-string.\n");
    } else if(!campoOK){ 
      printf("Campo já foi criado.\n"); // mensagem de erro caso campo inserido já exista
    }else{      
	strcpy(tabela_user.tab_L[j],nome_campo);
	tabela_user.tipos[j]=tipo_campo;
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
    if(tabela_user.tipos[j_id] == int_){
      idOK=1;
    } else{ 
      printf("ID invalido. O ID da tabela precisa conter inteiros positivos (tipo int).\n");
    }
  
  }while(!idOK);

  // guarde na tabela a linha de tipo
  fprintf(tabela_file,"%d;",tabela_user.tipos[j_id]); // tipo do id
  for(int j=0; j<tabela_user.C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%d;",tabela_user.tipos[j]);
  }
  fprintf(tabela_file,"\n");	

  // guarde na tabela a linha de campos
  fprintf(tabela_file,"%s;",tabela_user.tab_L[j_id]); // campo do id	
  for(int j=0; j<tabela_user.C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%s;",tabela_user.tab_L[j]);	
  }
  fprintf(tabela_file,"\n");	

  if(tabela_file == NULL){
    printf("Tabela não abriu!\n");
  }
  else{
    fclose(tabela_file);
  }

  // Registre a nova tabela no arquivo de relação de tabelas 
  relacao_file = fopen("relacaoTab", "a");
  fprintf(relacao_file,"%s %d\n",tabela_user.nome, tabela_user.C);	
 
  if(tabela_file == NULL){
    printf("Relação de tabelas não abriu!\n");
  }
  else{
    fclose(relacao_file);
  }

  // fazer o free de tabela_user.tab
  for(int j=0; j<tabela_user.C; j++)  
    free(tabela_user.tab_L[j]);

  free(tabela_user.tab_L);
  free(tabela_user.tipos);

}
void insereLinha_tab(char nome_tab[50], int n){
    FILE *tab_file;
    int temp;
    char str_temp[50];
    int i;
    int campoOK; //bool
  
    tabela tab;
    strcpy(tab.nome, nome_tab); 
    tab.C=n;
    //alocando vetores da struct
    tab.tab_L=malloc(sizeof(char*)*tab.C); //colunas alocadas
    for(int j=0; j<tab.C; j++)
    tab.tab_L[j]=malloc(sizeof(char)*50); // strings alocadas
  
    tab.tipos=malloc(sizeof(enum tipos_tab)*tab.C); //vetor de enum alocado


    tab_file = fopen(nome_tab, "r");
    

    //Leia a linha de tipos
    for(i=0; i<tab.C; i++){
       fscanf(tab_file," %[^;]s", str_temp);
       sscanf(str_temp,"%d", &temp);
       fgetc(tab_file);
       tab.tipos[i]=temp;
       //printf("%s %d\n", str_temp, tab.tipos[i]);

    }
    //Leia a linha dos campos
    for(i=0; i<tab.C; i++){
       fscanf(tab_file," %[^;]s", str_temp);
       fgetc(tab_file);
       strcpy(tab.tab_L[i], str_temp);
       //printf("temp: %s  tab.tab_L: %s\n", str_temp, tab.tab_L[i]);
    }
    fclose(tab_file);
    tab_file = fopen(nome_tab, "a");

    if(tab_file == NULL){
      printf("Relação de tabelas não abriu!\n");
    }
    i=0;
    do{
        campoOK=1;
        conversao_tipos(tab.tipos[i], str_temp);
	printf("Insira o campo %s (tipo: %s )\n", tab.tab_L[i],str_temp);
	scanf(" %[^\n]s", str_temp);
        if(i==0){
	       	for(int j=0; j<strlen(str_temp); j++){
			if(isdigit(str_temp[j]) == 0){ 
                             campoOK=0;
                             printf("O parametro tem que ser do tipo INT\n");
			     break;
 			}		    	
                }
		
		if(campoOK && strlen(str_temp) > 10){ //10 digitos é o tamanho máximo de um unsigned int
			campoOK=0;
			printf("Erro! Parametro não cabe em um inteiro\n");
		}
        }
	
        if(campoOK){
        	i++;
  		fprintf(tab_file, "%s;", str_temp);
	}
    }while(i<tab.C);
    fprintf(tab_file,"\n");


    if(tab_file == NULL){
      printf("Relação de tabelas não abriu!\n");
    }
    else{
     fclose(tab_file);
  }
  
 
   
}


int main(void) {
  FILE *tabela_file, *relacao_file;
  char op;
  char input[50], str_aux[50];
  int continua, existe; //bool
  int temp;

  printf("Bem vindo ao SGBD KI! - vs beta - \n");

  continua=1;
  do{
    printf("\n ***** MENU ***** \n");
    printf("1 - Criar tabela\n");
    printf("2 - Listar tabelas existentes\n");
    printf("3 - Inserir linha em tabela\n");
    printf("s - sair\n\n");

    scanf(" %c",&op);

    switch (op){
    case '1':
      cria_tab();
      break;
    case '2':
      listagem_tab();
      break;
    case '3':
      //checa_tab();
      printf("Qual a tabela que deseja acessar?\n");
      scanf(" %s",input);
      relacao_file = fopen("relacaoTab", "r");
      
      existe=0;
      while(fscanf(relacao_file,"%s %d\n",str_aux, &temp)!=EOF){ //enquanto não for End of File, continue imprimindo
       if(strcmp(str_aux, input)==0){
	      existe=1;
        break;
        }
      }
      fclose(relacao_file);
      if(existe){
        insereLinha_tab(input, temp);
      }
      else{
       printf("Tabela não existe!\n");
      }
      break;
    case 's':
      printf("Tchau!\n");
      continua=0;
      break;
    default:
      printf("Opção inválida. \n");
      break;
   
  }

  }while(continua);

  return 0;
}
