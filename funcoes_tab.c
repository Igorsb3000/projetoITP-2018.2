#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // macros dos limites dos tipos int, uint, char, entre outra
#include "lista_func.h"

tabela *alocaStruct_tab(int col){ 
  int i;
  tabela *tab;

  tab=malloc(sizeof(tabela));
  
  //alocando vetores da struct
  tab->tab_L=malloc(sizeof(char*)*col); //colunas alocadas
  for(i=0; i<col; i++)
    tab->tab_L[i]=malloc(sizeof(char)*50); // strings alocadas
  
  tab->tipos=malloc(sizeof(enum tipos_tab)*col); //vetor de enum alocado

  return tab;
}

void fillStruct_tab(tabela *tab, char nome_tab[50], int col){ 
  FILE *tab_file;
  int i,temp;
  char str_temp[50];
  
  strcpy(tab->nome, nome_tab); 
  tab->C=col;

  tab_file = fopen(nome_tab, "r");    
  if(tab_file == NULL)
    printf("\nALERTA: Tabela na linha %d não abriu!\n",__LINE__);

  // Leia a linha de tipos
  for(i=0; i<tab->C; i++){
    fscanf(tab_file," %[^;]s", str_temp);
    sscanf(str_temp,"%d", &temp);
    fgetc(tab_file);
    tab->tipos[i]=temp;
  }

  // Leia a linha dos campos
  for(i=0; i<tab->C; i++){
    fscanf(tab_file," %[^;]s", str_temp);
    fgetc(tab_file);
    strcpy(tab->tab_L[i], str_temp);
  }
  
  fclose(tab_file);

}

void freeStruct_tab(tabela *tab){
  int j;
  
  for(int j=0; j<tab->C; j++)  
    free(tab->tab_L[j]);

  free(tab->tab_L);
  free(tab->tipos);
}

void conversao_tipos(enum tipos_tab TIPO, char str_tipo[10]){
  char tipos_all[][10]={"int", "float", "double", "char", "string"};
  strcpy(str_tipo, tipos_all[TIPO-1]);
}

// checagem se valor de campo é compatível com o tipo do campo
int checaLimite_campos(char campo[50], enum tipos_tab tipo_campo){
  int campoOK=1; // bool
  int i, n_pontos=0;
  double x_temp;
  char c_temp, tipo_temp[10];

  //  printf("%d: %d\n",__LINE__,campoOK);
  if(tipo_campo==int_){

      if(isdigit(campo[0])==0 && campo[0]!='+' && campo[0]!='-')
	campoOK=0;
      
      for(i=1;i<strlen(campo);i++){
	if(isdigit(campo[i])==0){ 
	  campoOK=0;
	  break;
	}		    	
      }
      
      if(campoOK){
	sscanf(campo,"%lf",&x_temp);
	if(x_temp<INT_MIN || x_temp>INT_MAX)
	  campoOK=0;
      }
      
    } else if(tipo_campo==float_){ 

    if(isdigit(campo[0])==0 && campo[0]!='+' && campo[0]!='-')
      campoOK=0;
    
    for(i=1;i<strlen(campo);i++){
      if(campo[i]=='.')
	n_pontos++;
      
      if((isdigit(campo[i])==0 && campo[i]!='.') || n_pontos>1){ 
	campoOK=0;
	break;
      }		    	
    }
    
    } else if(tipo_campo==double_){ 

    if(isdigit(campo[0])==0 && campo[0]!='+' && campo[0]!='-')
      campoOK=0;
    
    for(i=1;i<strlen(campo);i++){
      if(campo[i]=='.')
	n_pontos++;
      
      if((isdigit(campo[i])==0 && campo[i]!='.') || n_pontos>1){ 
	campoOK=0;
	break;
      }		    	
    }

    } else if(tipo_campo==char_){
      if(strlen(campo)>1 || isalpha(campo[0])==0)
	campoOK=0;

      if(campoOK){
	sscanf(campo,"%c",&c_temp);
	if(c_temp<CHAR_MIN || c_temp>CHAR_MAX)
	  campoOK=0;
      }
    }

  if(!campoOK){
    conversao_tipos(tipo_campo,tipo_temp);
    printf("\n>>> ERRO: Campo passado precisa ser do tipo %s.\n\n",tipo_temp);
  }
  
  return campoOK;
}

//Função para listar todas tabelas
void listagem_tab(){ 
  FILE *relacao_file;
  char nome[50];
  int n;
  
  printf("\n *** Tabelas existentes ***\n");

  relacao_file = fopen("relacaoTab", "r");

  while(fscanf(relacao_file,"%s %*d\n",nome)!=EOF){ // enquanto não for End of File, continue imprimindo
    printf("%s\n",nome);
  }

  if(relacao_file == NULL){
    printf("Relação de tabelas não existe!\n");
  }
  else{
    fclose(relacao_file);
  }

}

// Função para criar uma nova tabela
void cria_tab(){ //>>>>>>>>>>>já usa funcao alocação<<<<<<<<<<<<<
  FILE *tabela_file, *relacao_file;
  tabela *tabela_user;
  int i,j;
  char nome_campo[50], nome_tab[50], str_temp[50];
  int tipo_campo, quant_campos; 
  int campoOK, idOK, id_int; // bool

  
  do{
    campoOK=1;
    printf("Digite o nome da tabela: "); 
    scanf(" %s", nome_tab);  
    strcat(nome_tab,".tab"); 

    relacao_file=fopen("relacaoTab","r");
    if(relacao_file==NULL){
      printf("\nPrimeira tabela criada no sistema.\n\n");
      break;
    }

    while(fscanf(relacao_file," %s %*d",str_temp)!=EOF){
      if(strcmp(nome_tab,str_temp)==0){
		campoOK=0;
		printf("\n>>> ERRO: tabela já existe.\n\n");
		break;
      }
    }
    
    fclose(relacao_file);
  } while(!campoOK);
 
  printf("Quantos campos irá inserir?\n");
  scanf("%d", &quant_campos);  
 
  //>>>>>alocando vetores da struct
  tabela_user=alocaStruct_tab(quant_campos); 
  strcpy(tabela_user->nome, nome_tab);
  tabela_user->C=quant_campos;

  j=0;
  do{
    tipo_campo=0;
    printf("\nInsira o campo[%d](sem espaços) e o seu tipo\n\n 1-int\n 2-float\n 3-double\n 4-char\n 5-string\n\n", j+1);
    scanf(" %s %d", nome_campo, &tipo_campo); 

    // verifique que os campos inseridos são únicos		
    campoOK=1;
    for(int i=0; i<j; i++){
      if(strcmp(tabela_user->tab_L[i],nome_campo)==0){
	campoOK=0;
	break;
      }
    }

    // Se for o último campo, VERIFICAR SE TEM UM CAMPO DISPONIVEL PARA SER UM ID
    if(j==(tabela_user->C-1)){ 

      id_int=0;
      for(i=0;i<j;i++){
	if(tabela_user->tipos[i]==1){ 
	  id_int=1;
	  break;
	}
      }
      
      if(tipo_campo==1)
	id_int=1;
    }
	
    if(tipo_campo != 1 && tipo_campo != 2 && tipo_campo != 3 && tipo_campo != 4 && tipo_campo != 5){
      printf("\n>>> ERRO: Os tipos precisam ser: 1-int, 2-float, 3-double, 4-char ou 5-string.\n\n");
    } else if(!campoOK){ 
      printf("\n>>> ERRO: Campo já foi criado.\n\n"); 
    } else if(!id_int){ 
      printf("\n>>> ERRO: Insira um campo obrigatoriamente do tipo int para ser o ID.\n\n");
    } else{      
      strcpy(tabela_user->tab_L[j],nome_campo);
      tabela_user->tipos[j]=tipo_campo;
      j++;
    }

  } while(j<tabela_user->C);

  // Criando campo de id
  int j_id;
  do{
    idOK=0;
    do{
      campoOK=0;
      printf("Qual dos campos é o ID da tabela? \n");
      scanf(" %s",nome_campo);
  
      // verificar se campo ID passado existe
      for(int j=0; j<tabela_user->C; j++){
	if(strcmp(tabela_user->tab_L[j],nome_campo)==0){
	  campoOK=1;
	  j_id=j;
	  break;
	}
      }

      if(!campoOK){
	printf("\n>>> ERRO: Campo inexistente. \nOs campos passados são: \n\n");
	for(int j=0; j<tabela_user->C; j++)
	  printf("%s ",tabela_user->tab_L[j]);
	printf("\n");
      }
    }while(!campoOK);
  
    // verifique se o id da tabela é valido
    if(tabela_user->tipos[j_id] == int_){
      idOK=1;
    } else{ 
      printf("\n>>> ERRO: ID invalido. O ID da tabela precisa conter inteiros positivos (tipo int).\n\n");
    }
  
  }while(!idOK);

  tabela_file = fopen(nome_tab,"wr+");
    
  // guarde na tabela a linha de tipo
  fprintf(tabela_file,"%d;",tabela_user->tipos[j_id]); // tipo do id
  for(int j=0; j<tabela_user->C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%d;",tabela_user->tipos[j]);
  }
  fprintf(tabela_file,"\n");	

  // guarde na tabela a linha de campos
  fprintf(tabela_file,"%s;",tabela_user->tab_L[j_id]); // campo do id	
  for(int j=0; j<tabela_user->C; j++){
    if(j!=j_id)
      fprintf(tabela_file,"%s;",tabela_user->tab_L[j]);	
  }
  fprintf(tabela_file,"\n");	

  if(tabela_file == NULL){
    printf("\nALERTA: Tabela na linha %d não abriu!\n\n",__LINE__);
  }
  else{
    fclose(tabela_file);
  }

  // Registre a nova tabela no arquivo de relação de tabelas 
  relacao_file = fopen("relacaoTab", "a");
  fprintf(relacao_file,"%s %d\n",tabela_user->nome, tabela_user->C);	
 
  if(tabela_file == NULL){
    printf("\nALERTA: Relação de tabelas na linha %d não abriu!\n",__LINE__);
  }
  else{
    fclose(relacao_file);
  }

  // fazer o free de tabela
  freeStruct_tab(tabela_user);

}

void insereLinha_tab(char nome_tab[50], int n){//>>>>>>>>>>>já usa funcao alocação<<<<<<<<<<<<<
  FILE *tab_file;
  char str_temp[50], id_file[50];
  int i,j,temp;
  int campoOK; //bool
  double x_temp;
  
  tabela *tab;
 
  tab=alocaStruct_tab(n);

  tab_file = fopen(nome_tab, "r");    
  if(tab_file == NULL)
    printf("\nALERTA: Arquivo na linha %d não abriu!\n\n",__LINE__);
  	
  	fillStruct_tab(tab, nome_tab, n);

  i=0;
  do{
    campoOK=1;
 
    conversao_tipos(tab->tipos[i], str_temp);
    printf("Insira o campo %s (tipo: %s )\n", tab->tab_L[i],str_temp);
    scanf(" %[^\n]s", str_temp);
    
    if(i==0){
      // cheque se chave passada é um unsigned int
    for(j=0; j<strlen(str_temp); j++){
		if(isdigit(str_temp[j]) == 0){ 
	  	campoOK=0;
	  	printf("\n>>> ERRO: campo ID precisa ser do tipo unsigned int.\n\n");
	  	break;
	}		    	
      }
		
    if(campoOK){
      sscanf(str_temp,"%lf",&x_temp);
      if(0>x_temp || x_temp>UINT_MAX){
	campoOK=0;
	printf("\n>>> ERRO: campo passado não cabe em um unsigned int.\n\n");
      } else{
	// checagem se id é único
	tab_file = fopen(nome_tab, "r");
	if(tab_file == NULL)
	  printf("\nALERTA: Tabela na linha %d não abriu!\n",__LINE__);
	  
	j=0; // pule linha de tipos e campos do arquivo
	while(fscanf(tab_file, " %[^;]s", id_file)!=EOF){
	  fscanf(tab_file, " %*[^\n]s");
	  if(j>1 && strcmp(str_temp,id_file)==0){ 
	    printf("\n>>> ERRO: ID %s já existe!\n\n",str_temp);
	    campoOK=0;
	    break;
	  }
	  j++;
	}

	fclose(tab_file);
      }	
    }
    } else{
      campoOK=checaLimite_campos(str_temp,tab->tipos[i]);
      if(tab->tipos[i] == string_){

	if(strcmp(str_temp, "NULL")==0){
	  campoOK=0;
	  printf("\n>>>ERRO: string reservada pelo sistema.\n\n");
	}
      }
    }
    
    if(campoOK){
      i++;
    
      tab_file = fopen(nome_tab, "a");
      if(tab_file == NULL)
	printf("\nALERTA: Tabela na linha %d não abriu!\n",__LINE__);
      
      fprintf(tab_file, "%s;", str_temp);
      fclose(tab_file);
    }
    
  } while(i<tab->C);

  tab_file = fopen(nome_tab, "a");
  if(tab_file == NULL)
    printf("\nALERTA: Tabela na linha %d não abriu!\n",__LINE__);
  
  fprintf(tab_file,"\n");
  fclose(tab_file);

  // fazer o free de tabela
  freeStruct_tab(tab);
  
}


void editar_tab(char nome_tab[50], int n){//>>>>>>>>>>>já usa funcao alocação<<<<<<<<<<<<<
 FILE *tab_file,*file_temp;
  char str_temp[50], id_file[50];
  int i,cont;
  int campoOK,existe_id; //bool
  char chave[10],chave_user[10],c_temp;
  long int pos;

  tabela *tab; //tipo struct tabela_t

  tab=alocaStruct_tab(n);  
  fillStruct_tab(tab, nome_tab, n);

  // Pede a chave primária(ID), caso não exista repete o processo
  tab_file = fopen(nome_tab, "r+");
  do{ 
    printf("Insira o ID da linha: ");
    scanf(" %s", chave_user);

    cont=0;
    existe_id=0;
    while(fscanf(tab_file," %[^;]s", chave)!=EOF){
      if(cont>=2 && strcmp(chave, chave_user)==0){
	existe_id=1;
	pos=ftell(tab_file);
	break;
      }
      fscanf(tab_file, " %*[^\n]s");
      cont++;
    }

    if(existe_id)
      printf("Achei o ID %s.\n", chave);
    else
      printf("\n>>> ERRO: ID não existe.\n\n");

    rewind(tab_file);
  } while(!existe_id);
    
  // copia arquivo até id da linha que será editada
  file_temp=fopen("fileTemp","w+");
  if(file_temp==NULL)
    printf("\nALERTA: Arquivo na linha %d não abriu!\n\n",__LINE__);
    
  cont=0;
  while(cont<=pos){
    c_temp=fgetc(tab_file);
    fprintf(file_temp,"%c",c_temp);
    cont++;
  }

  // armazena linha conforme campos passados pelo usuário
  i=1;
  do{
    printf("Entre com o campo %s (tipo: %d):",tab->tab_L[i],tab->tipos[i]);
    scanf(" %[^\n]s",str_temp);
    campoOK=checaLimite_campos(str_temp,tab->tipos[i]);
    if(campoOK){
      fprintf(file_temp,"%s;",str_temp);
      i++;
    }
  } while(i<tab->C);
  fprintf(file_temp,"\n");
    
  // copia restante 
  fscanf(tab_file, " %*[^\n]s");
  fgetc(tab_file);
  while((c_temp=fgetc(tab_file))!=EOF){ 
    fprintf(file_temp,"%c",c_temp);
  }
    
  fclose(file_temp);
  fclose(tab_file);

  remove(tab->nome);
  rename("fileTemp",tab->nome);

  freeStruct_tab(tab);


}

void insereColuna_tab(char nome_tab[50], int n){

  FILE *tab_file, *file_temp, *relacao_file;
  char str_temp[50], id_file[50], nome_campo[50];
  int i,j,temp, tipo_campo;
  int campoOK; //bool
  double x_temp;
  
  tabela *tab;
 
  tab=alocaStruct_tab(n+1);  	
  fillStruct_tab(tab, nome_tab, n);	

  do{
    tipo_campo=0;
    printf("\nInsira o campo[%d](sem espaços) e o seu tipo\n\n 1-int\n 2-float\n 3-double\n 4-char\n 5-string\n\n", tab->C+1);
    scanf(" %s %d", nome_campo, &tipo_campo); 

    campoOK=1;
    //verificar se o campo já existe
    for(int i=0; i<tab->C; i++){
      if(strcmp(tab->tab_L[i],nome_campo)==0){
	campoOK=0;
	break;
      }
    }
    
    //verificar se o tipo é válido
    if(tipo_campo != 1 && tipo_campo != 2 && tipo_campo != 3 && tipo_campo != 4 && tipo_campo != 5){
      printf("\n>>> ERRO: Os tipos precisam ser: 1-int, 2-float, 3-double, 4-char ou 5-string.\n\n");
    } else if(!campoOK){ 
      printf("\n>>> ERRO: Campo já foi criado.\n\n"); // mensagem de erro caso campo inserido já exista
    }else{      
      strcpy(tab->tab_L[tab->C],nome_campo);
      tab->tipos[tab->C]=tipo_campo;
    } 

  }while(!campoOK);

  
  tab_file = fopen(nome_tab, "r"); 

  file_temp=fopen("fileTemp","w+");
  
  if(file_temp==NULL){
    printf("\nALERTA: Arquivo na linha %d não abriu!",__LINE__);
  }


  char aux2[50];
  char str_tipo[10];
  int cont;
  long int pos;
  char c_temp;
  int campo_OK, num;
  char aux[50];
  
  cont=0;
  i=0;
  while(fscanf(tab_file," %[^;]s", aux2)!=EOF){ 
    fprintf(file_temp, "%s;", aux2);
    fgetc(tab_file);

  		
    if(cont==tab->C-1 && i==0){
      cont=-1;
      i++;
      fprintf(file_temp, "%d;", tipo_campo);
      fprintf(file_temp, "\n");
    }

    if(cont==tab->C-1 && i==1){
      cont=-1;
      i++;
      fprintf(file_temp, "%s;", nome_campo);
      fprintf(file_temp, "\n");
  			
    }
    if(cont==tab->C-1 && i>1){
      cont=-1;
      i++; // conta o numero de linhas
      fprintf(file_temp, "%s;", "NULL");
      fprintf(file_temp, "\n");
    }

    cont++; // conta o número de campos
  	
  }

  fclose(file_temp);
  remove(tab->nome);
  rename("fileTemp",tab->nome);
		

  relacao_file = fopen("relacaoTab", "r");
    
  if(relacao_file == NULL){
    printf("\nALERTA: Relação de tabelas na linha %d não abriu!\n",__LINE__);
  }
  		

  file_temp=fopen("fileTemp","w+");
	
  //Copiando o arquivo relacaoTab para um temporário até a tabela a ser substituida
  while(fscanf(relacao_file," %s %d", aux2, &num)!=EOF){
    if(strcmp(aux2, nome_tab)==0){
      fprintf(file_temp, "%s %d", aux2, num+1);
      fprintf(file_temp, "\n");
    }else{
      fprintf(file_temp, "%s %d", aux2, num);
      fprintf(file_temp, "\n");
    }

  }
		  
  if(file_temp==NULL)
    printf("\nALERTA: Arquivo na linha %d não abriu!\n\n",__LINE__);
		  
  		
  fclose(relacao_file);
  remove("relacaoTab");
  rename("fileTemp","relacaoTab");
  fclose(file_temp);
  
  // fazer o free de tabela
  freeStruct_tab(tab);

}

void listarDados_tab(char nome_tab[50], int n){

  FILE *tab_file;
  char str_temp[50];
  int line,col,maior;
  
  tabela *tab;
 
  tab=alocaStruct_tab(n);
  fillStruct_tab(tab, nome_tab, n);	

  tab_file=fopen(nome_tab,"r");
  if(tab_file==NULL)
    printf("\nALERTA: tabela não abriu na linha %d.\n\n",__LINE__);

  maior=0;
  while(fscanf(tab_file," %[^;]s",str_temp)!=EOF){
    if(strlen(str_temp)>maior)
      maior=strlen(str_temp);
      fgetc(tab_file); // pule delimitador ; 
  }

  rewind(tab_file);
  printf("\n***** TABELA %s *****\n",nome_tab);

  line=0; col=0; 
  while(fscanf(tab_file," %[^;]s",str_temp)!=EOF){

    if(line>0){
    	if(strcmp(str_temp,"NULL")==0){
    		printf("%-*s ",maior+5," ");
    	}else{
      		printf("%-*s ",maior+5,str_temp);
      	}

  	}

      fgetc(tab_file); // pule delimitador ; 
      col++;

    if(col==tab->C){
      printf("\n");
      line++;
      col=0;
    }

  }
  printf("\n***** FIM *****\n\n");

  fclose(tab_file);

  freeStruct_tab(tab);
}

void pesquisarDados_tab(char nome_tab[50], int n){

	FILE *tab_file, *file_temp, *relacao_file;
  	char str_temp[50], aux[50];
  	int i,j,temp, tipo_campo, maior, col, line;
  	int campoOK; //bool
  	double x_temp;
  
  	tabela *tab;
 
  	tab=alocaStruct_tab(n);
  	
  	fillStruct_tab(tab, nome_tab, n);

 	tab_file=fopen(nome_tab,"r");
  	if(tab_file==NULL)
    	printf("\nALERTA: tabela não abriu na linha %d.\n\n",__LINE__); 

    maior=0;
  while(fscanf(tab_file," %[^;]s",str_temp)!=EOF){
    if(strlen(str_temp)>maior)
      maior=strlen(str_temp);
    	fgetc(tab_file); // pule delimitador ; 
  }

  rewind(tab_file);
  printf("\n***** COLUNAS DISPONÍVEIS *****\n");

  line=0; col=0; 
  while(fscanf(tab_file," %[^;]s",str_temp)!=EOF){

    if(line==1)
      	printf("%-*s ",maior+2,str_temp);
    	fgetc(tab_file); // pule delimitador ; 
    	col++;

    if(col==tab->C){
      printf("\n");
      line++;
      col=0;
    }

  }
  printf("Digite a coluna para realizar a pesquisa: \n");
  scanf(" %[^\n]s", aux);
  rewind(tab_file);
  line=0;
  while(fscanf(tab_file," %[^;]s",str_temp)!=EOF){
    if(line==1){
    	if(strcmp(aux, str_temp)==0){
    		printf("O campo escolhido foi: %s\n", aux);
    	}
    	fgetc(tab_file);
    }else{
    	fgetc(tab_file);
    	line++;
    	}
	}


  fclose(tab_file);

  freeStruct_tab(tab);
}

