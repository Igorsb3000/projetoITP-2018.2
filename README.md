# projetoITP-2018.2
Sistema de Gerenciamento de Banco de Dados relacional KI 

Todas as funcionalidades solicitadas (item 1-9) foram implementadas. 
Uma funcionalidade extra foi feita, adicionando ao item 7 a possibilidade de fazer uma pesquisa parcial (substring) nos dados do tipo string de uma tabela. O usuário deve utilizar o char * para indicar o que pode ser omitido na busca, por exemplo *str ou str* ou str*str, no primeiro caso o sistema retorna todos os dados da tabela que encontram str no fim da coluna solicitada...


Listagem do que faríamos de forma diferente:

* usaria o fgets ao invés do fgetc (dizer os pros e contras de cada um)
* otimizar a abertura de arquivo
* modularização desde o início
* um planejamento maior do projeto inicial

O projeto pode ser compilado com o makefile disponível. O executável gerado é 'kiexe'.
Precisa instalar o strcastr???


** Autores ***
Karine Piacentini Coelho da Costa
Igor Silva Bento

O trabalho foi feito em conjunto.
