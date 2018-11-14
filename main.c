/* 
Problemas:
- Código fica preso se na hora de escolher qual dos campos é o ID na função cria_tabela, nenhum dos campos fornecidos anteriormente for int. O código deve abortar e permitir que a pessoa tente criar a tabela novamente.
- verificar na função checaLimite_campos se campo passado cabe no campo: caso float e double (não é assim que faz...)
- definir tamanho máximo dos campos com uma constante
- testar/implementar funções aloca/fill_struct
- fazer a cópia de arquivo no edita_linha mais eficiente
- impedir que se crie tabela que já existe
Melhorias:
- coversão de tipos pode retornar um string constane de modo a não precisar declarar variáveis para utilizá-lo?
- Minimizar a abertura de arquivos
- Mensagens de error de abertura de tabela mostram qual a linha e param o código
Dúvidas:
- No insereLinha_tab(), estamos conferindo se string passada é compatível com tipo do campo. Estamos fazendo da melhor maneira?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // macros dos limites dos tipos int, uint, char, entre outros 
#include "lista_func.h"

int main(void) {
  FILE *tabela_file, *relacao_file;
  char op;
  char input[50], str_aux[50];
  int continua, existe; //bool
  int temp, temp2;
  char aux[10];

  printf("Bem vindo ao SGBD KI! - vs beta - \n");

  continua=1;

  do{
    printf("\n ***** MENU ***** \n");
    printf("1 - Criar tabela\n");
    printf("2 - Listar tabelas existentes\n");
    printf("3 - Inserir linha em tabela\n");
    printf("4 - Editar colunas da tabela\n");
    printf("5 - Inserir coluna na tabela\n");
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

      if(existe)
        insereLinha_tab(input, temp);
      else
        printf("Tabela não existe!\n");

      break;
    case '4':
      printf("Qual a tabela que deseja acessar?\n");
      scanf(" %s",input);
      
      relacao_file = fopen("relacaoTab", "r");
      existe=0;
      while(fscanf(relacao_file,"%s %d\n",str_aux, &temp2)!=EOF){ //enquanto não for End of File, continue 
       if(strcmp(str_aux, input)==0){
         existe=1;
         break;
        }
      }

      fclose(relacao_file);
      if(existe)
        editar_tab(input, temp2);
      else
         printf("Tabela não existe!\n");
      
      break;
    case '5':
      printf("Qual a tabela que deseja acessar?\n");
      scanf(" %s",input);
      
      relacao_file = fopen("relacaoTab", "r");
      existe=0;
      while(fscanf(relacao_file,"%s %d\n",str_aux, &temp2)!=EOF){ //enquanto não for End of File, continue 
       if(strcmp(str_aux, input)==0){
         existe=1;
         break;
        }
      }

      fclose(relacao_file);
      if(existe)
        insereColuna_tab(input, temp2);
      else
         printf("Tabela não existe!\n");
      
      break;
    case 's':
      printf("Tchau!\n");
      continua=0;
      break;
    default:
      printf("Opção inválida. \n");
      break;
    }

  } while(continua);

  return 0;
}
