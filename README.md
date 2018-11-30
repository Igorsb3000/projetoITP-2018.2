# projetoITP-2018.2
Sistema de Gerenciamento de Banco de Dados relacional KI 

Todas as funcionalidades solicitadas (item 1-9) foram implementadas. 
Uma funcionalidade extra foi feita, adicionando ao item 7 a possibilidade de fazer uma pesquisa parcial (substring) nos campos do tipo string de uma tabela. O usuário deve utilizar o char '*' para indicar o que pode ser omitido na busca. Foram implementadas as buscas pelas seguintes expressões regulares: *str ou str* ou str*str.


Listagem do que faríamos de forma diferente:

* Usaria o fgets ao invés de utilizar as funções fscanf e fgetc. O fgets permite uma checagem de erro de leitura mais facilmente, o que permite o sistema perceber um arquivo corrompido, por exemplo. O que é mais difícil de fazer utilizando o fscanf.
* Utilizaríamos a modularização desde o início do projeto. (Implementamos essa parte a partir do item 4 apenas)
* Um planejamento maior do projeto inicial.

O projeto pode é executado da seguinte forma:
1. No terminal, digite:
> make

2. Em seguida, digite:
> ./kiexe


** Autores ***

Karine Piacentini Coelho da Costa

Igor Silva Bento


O trabalho foi feito em conjunto.
