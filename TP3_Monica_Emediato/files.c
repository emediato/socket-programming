#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "files.h"

/*
Nome: Mônica Emediato
*/

void begintp()
{
	FILE *fp;
	fp = fopen("users.txt","w");	//Cria arquivo de controle de registro de usuarios e senhas
	if(fp==NULL)
	{
		printf("Erro ao abrir arquivo");
	}
	fclose(fp);
}

char *new_user(char *login, char *senha)
{
	FILE *files;
	char *result = malloc(5*sizeof(char));
	char *usertemp = malloc(15*sizeof(char));
	files = fopen("users.txt","r");
	if(files==NULL)
	{
		printf("ERRO AO ABRIR ARQUIVO\n");
	}
	while((fscanf(files,"%s\n",usertemp))!=EOF)		//Lê todo o arquivo de controle
	{
		if(!(strcmp(usertemp,login)))		//Se achar usuário
		{
			result = "N -1";
			fclose(files);
			return result;
		}
	}
	fclose(files);
	files = fopen("users.txt","a+");		//Se não achar, adiciona o novo usuario
	if(files==NULL)
	{
		printf("ERRO AO ABRIR ARQUIVO\n");
	}
	else
	{
		fprintf(files, "%s %s ", login, senha);
		fclose(files);
		result = "N 0";
		char *lista = malloc(20*sizeof(char));
		strncpy(lista,login,15);
		strcat(lista,"_files.txt");
		files = fopen(lista,"w");
	}
	fclose(files);
	return result;
}


char *sendmsgtp(char *login, char *senha, char *book, char *message)
{
	FILE *files;
	char *result = malloc (5*sizeof(char));
	char *senhatemp = malloc (15*sizeof(char));
	char *logintemp = malloc (15*sizeof(char));


	files = fopen("users.txt","r");
	if(files == NULL)
	{
		printf("ERRO AO ABRIR O ARQUIVO\n");
	}
	else
	{
		while((fscanf(files,"%s %s ",logintemp,senhatemp))!=EOF)		//busca o usuario e senha no arquivo de usuarios
		{
			if(strcmp(login,logintemp)==0)		//Se achar o usuário
			{
				fclose(files);
				if(strcmp(senha,senhatemp)!=0)		//Se a senha for errada
				{
					result = "S -2";
					return result;
				}
				else		//Se a senha for correta
				{
					char *arqname = malloc(20*sizeof(char));
					strncpy(arqname,login,15);
					strcat(arqname,"_");
					strcat(arqname,book);
					FILE *fp = fopen(arqname,"r");
					if(fp == NULL)		//Se o arquivo não existe
					{
						fp = fopen(arqname,"w");
						fprintf(fp,"%s",message);
						char *lista = malloc(20*sizeof(char));
						strncpy(lista,login,15);
						strcat(lista,"_files.txt");
						files = fopen(lista,"a");
						fprintf(files,"%s ",book);
						result = "S 0";
						fclose(files);
						fclose(fp);
						return result;
					}
					else		//Se o arquivo existe
					{
						
						fp = fopen(arqname,"w");
						fprintf(fp,"%s",message);
						result = "S 1";
						fclose(fp);
						return result;
					}
				}
			}
			else		//Se não encontrou o usuário
			{
				result = "S -1";
			}
		}
		
		
		
	}	
	fclose(files);
	return result;
}


char *readmsgtp(char *login, char *senha, char *book)
{
	FILE *files;
	char *result = malloc (10*sizeof(char));
	char *senhatemp = malloc (15*sizeof(char));
	char *logintemp = malloc (15*sizeof(char));

	files = fopen("users.txt","r");
	if(files == NULL)
	{
		printf("ERRO AO ABRIR O ARQUIVO\n");
	}
	else
	{
		while((fscanf(files,"%s %s ",logintemp,senhatemp))!=EOF)		//busca o usuario e senha no arquivo de usuarios
		{
			if(strcmp(login,logintemp)==0)		//Se achar o usuário
			{
				fclose(files);

				if(strcmp(senha,senhatemp)!=0)		//Se a senha for errada
				{
					result = "R -2";
					return result;
				}
				else		//Se a senha for correta
				{

					char *arqname = malloc(30*sizeof(char));
					strncpy(arqname,login,25);
					strcat(arqname,"_");
					strcat(arqname,book);
					FILE *fp;
					fp = fopen(arqname,"r");
					if(fp == NULL)		//Se o arquivo não existe
					{
						result = "R -3";
						return result;
					}
					else		//Se o arquivo existe
					{
	
						char *saida = malloc(105*sizeof(char));
						char *temp = malloc(105*sizeof(char));
						fgets(temp,100,fp);
						saida[0] = 'R';
						saida[1] = ' ';
						saida[2] = '0';
						saida[3] = ' ';
						saida[4] = '\0';
						strcat(saida,temp);
						fclose(fp);
						return saida;
						
						
					}
				}
			}
			else		//Se não encontrou o usuário
			{
				result = "R -1";
			}
		}
		
		
		
	}	
	fclose(files);
	return result;
}


char *list(char *login, char *senha)
{
	char *senhatemp = malloc (15*sizeof(char));
	char *result = malloc (10*sizeof(char));	
	char *logintemp = malloc (15*sizeof(char));
	FILE *files;
	files = fopen("users.txt","r");
	if(files == NULL)
	{
		printf("ERRO AO ABRIR O ARQUIVO\n");
	}
	else
	{
		while((fscanf(files,"%s %s ",logintemp,senhatemp))!=EOF)		//busca o usuario e senha no arquivo de usuarios
		{

			if(strcmp(login,logintemp)==0)		//Se achar o usuário
			{
				fclose(files);

				if(strcmp(senha,senhatemp)!=0)		//Se a senha for errada
				{
					result = "L -2";
					return result;
				}
				else		//Se a senha for correta
				{

					char *lista = malloc(20*sizeof(char));
					strncpy(lista,login,15);
					strcat(lista,"_files.txt");
					FILE *arq;
					arq = fopen(lista,"r");
					char *saida = malloc(100*sizeof(char));
					char *temp = malloc(105*sizeof(char));
					fgets(temp, 100, arq);	
					saida[0] = 'L';
					saida[1] = ' ';
					saida[2] = '0';
					saida[3] = ' ';
					saida[4] = '\0';
					strcat(saida,temp);
					fclose(arq);
					return saida;
				}
			}
			else		//Se não achar o usuário
			{
				result = "L -1";
			}
		}
	}
	fclose(files);
	return result;
}

