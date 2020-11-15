#ifndef FILES_H_
#define FILES_H_

/*
Nome: Mônica Emediato

Para a implementação dos códigos, foram utilizados um main para o cliente, um
main para o servidor e uma biblioteca “files.h” que o servidor utilizou para tratar as
mensagens.


*/


/*********************************************************************************
Nome: New_user
Entrada: char* login, char* senha
Saída: char* result
descrição: Recebe um usuário e senha e cadastra eles no arquivo users.txt ou retor
-na -1 caso o usuário já exista
*********************************************************************************/
char *new_user(char *login, char *senha);

/*********************************************************************************
Nome: Sendmsgtp
Entrada: char *login, char *senha, char *book, char *message
Saída: char *buffer
descrição: Envia uma mensagem de upload de conteudo de texto ou sinaliza erro.
*********************************************************************************/
char *sendmsgtp(char *login, char *senha, char *book, char *message);

/*********************************************************************************
Nome: Begintp
Entrada: void
Saída: void
descrição: Cria arquivo inicial de usuarios e senhas.
*********************************************************************************/
void begintp();

/*********************************************************************************
Nome: Readmsgtp
Entrada: char *login, char *senha, char *book
Saída: char* result
descrição: Recebe usuario, senha, nome do arquivo e exibe o conteudo do arquivo ou
em caso de erro, sinaliza-o.
*********************************************************************************/
char *readmsgtp(char *login, char *senha, char *book);

/*********************************************************************************
Nome: List
Entrada: char *login, char *senha
Saída: char *result
descrição: Recebe login e senha e retorna os arquivos de texto do usuario ou então
reporta erro
*********************************************************************************/
char *list(char *login, char *senha);


#endif
