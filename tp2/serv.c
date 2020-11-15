/* 
 *TP3 - Trabalho prático. Protocolo olímpico.
   Servidor usando o protocolo TCP.
   Aceita IPv6 e IPv4.
   Recebe dados do cliente na forma de tempo do tipo xxh xxm xxs xxms.
   Processa os dados recebidos, ordena e devolve a classificação de cada atleta.
   Trata várias conexões por vez.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#include "olim.h"   /* arquivo de cabeçalho do protocolo olimpico*/

#define MAX_LINE   256
#define af AF_INET6

void *connection_handler(void *);


int main (int argc, char *argv[])  {     

        
	struct sockaddr_storage ss;  /* estrutura de sockets genérica */
    struct addrinfo hints, *res; /* estruturas usadas na "getaddrinfo", "*res" conterá porta, tipo de sockets etc*/
    socklen_t addr_size = sizeof ss; /* tamanho da estrutura genérica a ser usada na função "accept"*/
    int sockfd, *new_fd, client_s;  /* socket do servidor e do cliente*/
    int PORT; 
    int  i=0, p=0;
    int cla[1000], t=0;  // cla[1000] é o vetor de classificação 

              

    if(argc != 2){
    	fprintf(stderr, "usage: simplex-talk Port\n");
        exit(1);
    }

    PORT = atoi(argv[1]);

    if(PORT <= 1024 ){
	    fprintf(stderr, "usage: simplex-talk Port\n");
        exit(1);
    }

    /* em primeiro lugar, carrega estruturas de endereço com getaddrinfo (): */

	memset(&hints, 0, sizeof hints); /* zera a estrutura*/
    hints.ai_family = af;  /* a família escolhida é a AF_INET6, pois aceita conexões IPv4 e IPv6*/
    hints.ai_socktype = SOCK_STREAM; /* o protocolo esperado para esta conexão é o TCP */ 
    hints.ai_flags = AI_PASSIVE;     /* flag sinalizando para preencher IP*/

	if(getaddrinfo(NULL, argv[1], &hints, &res)) { /* "argv[1]" é a porta recebida por parâmetro, res-> é um ponteiro para a estrutura*/
	    fprintf(stderr, "usage: simplex-talk getaddrinfo\n");
        exit(1);
    }

    /* prepara a abertura passiva*/

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	bind(sockfd, res->ai_addr, res->ai_addrlen);

	listen(sockfd, 100); 

    /* função para cada cliente com todas as variáveis necessárias e as estruturas de dados*/

    void *connection_handler(void *socket_desc){
		
        int sock = *(int*)socket_desc;
        char buf[MAX_LINE];
        int len;
        

       
        /*laço principal recebe linhas de texto e processa os dados*/       
        while(len = recv(sock, buf, sizeof(buf), 0))  {
      
           	if(buf[0] == '-') break;        		
              
        	t=0;
            t = temp_ms(buf);  //a variável t recebe o tempo total em ms do cliente
            if(t != 0)  {  // se tempo for diferente de '0', insere no vetor
            	cla[i] = t;
                i++;
                insercao(1000, cla); /* o metódo de ordenação "inserção" é aplicado ao vetor*/
                p = pos(t, cla);     // a variável 'p' recebe a posição depois da ordenação         
                printf("%d\n", p);    //imprime a posição do atleta
                    
            }     
        }
        close(sock);
        free(socket_desc);
    	return 0;
	}                 

    /* epera conexão, depois cria uma Thread para tratar cada conexão separadamente*/


    for(i=0; i<1000; i++) cla[i] = 0;  //inicializa vetor de classificação 
    i=0; 



	while(1){

		if((client_s = accept(sockfd, (struct sockaddr *)&ss, &addr_size)) < 0)  {
        	perror("simplex-talk: accept");
            exit(1);
        }

        pthread_t sniffer_thread;

        new_fd = malloc(1);
        *new_fd = client_s;

        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_fd) <0){
        	perror("erro ao criar thread"); 
            return 1;
        }
             
	}         
}

















            
