#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "files.h"

int main()
{
	char *login = malloc(15*sizeof(char));
	char *matricula = malloc(15*sizeof(char));
	char *result = malloc(10*sizeof(char));
	char *message = malloc(100*sizeof(char));
	char *book = malloc(50*sizeof(char));
	char *saida = malloc(105*sizeof(char));
	int i;
	begintp();
	printf("\nDigite o login: ");
	__fpurge(stdin);
	fflush(stdin);
	scanf("%s",login);
	printf("digite a matricula: ");
	__fpurge(stdin);
	fflush(stdin);
	scanf("%s",matricula);
	result = new_user(login,matricula);
	puts(result);
	printf("\nDigite o nome do arquivo: ");
	__fpurge(stdin);
	fflush(stdin);
	scanf("%s",book);
	printf("\nDigite o conteudo do arquivo: ");
	__fpurge(stdin);
	fflush(stdin);
	fgets(message,100,stdin);
	result = sendmsgtp(login, matricula, book, message);
	puts(result);	printf("\nDigite o nome do arquivo: ");
	__fpurge(stdin);
	fflush(stdin);
	scanf("%s",book);
	printf("\nDigite o conteudo do arquivo: ");
	__fpurge(stdin);
	fflush(stdin);
	fgets(message,100,stdin);
	result = sendmsgtp(login, matricula, book, message);
	puts(result);
	saida = readmsgtp(login,matricula,book);
	puts(saida);
	saida = list(login,matricula);
	puts(saida);

	return 0;
}
