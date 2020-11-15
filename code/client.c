/* 
 *TP3 - Trabalho prático. Protocolo olímpico. 
   Cliente usando o protocolo TCP.
   Aceita IPv6 e IPv4.
   Envia dados para o servidor na forma de tempo do tipo xxh xxm xxs xxms.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 256

int main (int argc, char *argv[]){ 

	struct addrinfo hints, *res; /* estruturas usadas na "getaddrinfo", "*res" conterá os dados de endereço, porta, tipo de sockets etc*/
    char buf[MAX_LINE]; /* armazena os dados a serem enviados ao servidor */
    int s;             /* socket do cliente */
    int len;
    int i;   

    if(argc != 3) {
    	fprintf(stderr, "usage: simplex-talk Port/host\n");
        exit(1);
    }       
    /* em primeiro lugar, carrega estruturas de endereço com getaddrinfo (): */
    memset(&hints, 0, sizeof hints); /* zera a estrutura*/
    hints.ai_family = AF_UNSPEC;     /* a família não está definida, pois aceita conexões IPv4 e IPv6*/
    hints.ai_socktype = SOCK_STREAM; /* o protocolo esperado para esta conexão é o TCP */ 
    hints.ai_flags = AI_CANONNAME;  /*ai_flags como AI_CANONNAME para que o hostname descoberto seja retornado na struct addrinfo */ 
      
    if(getaddrinfo(argv[1], argv[2], &hints, &res)) { /* "argv[1]" é o IP recebidO por parâmetro, "argv[2]" é a porta, "res->" é  
                                                            um ponteiro para a estrutura */
    	fprintf(stderr, "usage: simplex-talk getaddrinfo\n");
        exit(1);
    }      
    /* abertura ativa*/
    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(s < 0) {   
    	perror("simplex-talk: socket");
        exit(1);
    }

    if(connect(s, res->ai_addr, res->ai_addrlen) < 0) {   
    	perror("simplex-talk: connect");
        exit(1);
    }
    /* laço principal: obtém e envia linhas de texto */
    while(fgets(buf, sizeof(buf), stdin)) {
                                 
    	buf[MAX_LINE-1] = '\0';                
        len = strlen(buf) + 1;
        send(s, buf, len, 0); 
        for(i=0; i< 10000000; i++) { /* No caso do cliente ler arquivo texto.txt passado pelo operador '<' da linha de comando,
                                            deve-se colocar um atraso de tempo no cliente. Caso contrário o servidor não consegue processar
                                            os dados na mesma velocidade em que o cliente envia as informações.*/
        }
               
        /* verificação da condição que fecha a conexão*/
        if(buf[0] == '-'){ 
     	   close(s);
           exit(1);
        }

                               
     }
}
