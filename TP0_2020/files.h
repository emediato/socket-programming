#ifndef FILES_H_
#define FILES_H_

/*
Nome: Matheus Victor Ramos dos Anjos
TP3 - Cloud Text
Professor: Luiz Filipe
Monitor: Gabriel de Biasi
*/


/*********************************************************************************
Nome: New_user
Entrada: char* login, char* matricula
Saída: char* result
descrição: Recebe um usuário e matricula e cadastra eles no arquivo users.txt ou retor
-na -1 caso o usuário já exista
*********************************************************************************/
char *new_user(char *login, char *matricula);

/*********************************************************************************
Nome: Sendmsgtp
Entrada: char *login, char *matricula, char *book, char *message
Saída: char *buffer
descrição: Envia uma mensagem de upload de conteudo de texto ou sinaliza erro.
*********************************************************************************/
char *sendmsgtp(char *login, char *matricula, char *book, char *message);

/*********************************************************************************
Nome: Begintp
Entrada: void
Saída: void
descrição: Cria arquivo inicial de usuarios e matriculas.
*********************************************************************************/
void begintp();

/*********************************************************************************
Nome: Readmsgtp
Entrada: char *login, char *matricula, char *book
Saída: char* result
descrição: Recebe usuario, matricula, nome do arquivo e exibe o conteudo do arquivo ou
em caso de erro, sinaliza-o.
*********************************************************************************/
char *readmsgtp(char *login, char *matricula, char *book);

/*********************************************************************************
Nome: List
Entrada: char *login, char *matricula
Saída: char *result
descrição: Recebe login e matricula e retorna os arquivos de texto do usuario ou então
reporta erro
*********************************************************************************/
char *list(char *login, char *matricula);


#endif
