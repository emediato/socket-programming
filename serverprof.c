#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>

void usage (int argc, char **argv) { // recebe o tipo de serviidor do cliente
  printf("usage: %s <v4|v6> <server port\n>", argv[0]);
  printf ("example: %s v4 51511\n", argv[0]);
  exit(EXIT_FAILURE);
}

#define BUFSZ 1024

int main(int argc, char** argv) {
  if (argc < 3 ){
    usage(argc, argv);
  }
  struct sockaddr_storage storage;
  if ( 0 != server_sockaddr_init (argv[1], argv[2], &storage)){
    usage(argc, argv);
  }

  int s; //socket
  s = socket (storage.ss_family, SOCK_STREAM,0);
  if (s == -1 ){
    logexit("socket");
  }

  int enable = 1;
  if ( 0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))){
      logexit("setsockopt");
  }


  struct sockaddr *addr = (struct sockaddr *)(&storage); //cast

  if(0 != bind(s, addr, sizeof(storage))){ //qual o tamaho efetivo desse pedaço de memoria
    logexit("bind");
  }

  if(0 != listen(s, 10)){ //esperando conecoes
    logexit("listen");
  }
  char addrstr[BUFSZ];
  addrtostr(addr, addrstr, BUFSZ);
  printf("bound to%s, waiting connections \n", addrstr);
  //comunicacao cliente servidorTCP

  while(1) {

    struct sockaddr_storage cstorage; //endereco do cliente
    struct sockaddr *caddr = (struct sockaddr *) (&cstorage);
    socklen_t caddrlen = sizeof(cstorage);
    int csock = accept(s, caddr, &caddrlen); //accept sabe de onde vem o cliente e ele pasa o cliente
    //accept pode mudar o tamanho dependendo do tamanho do protocolo
    if (csock == -1 ) {
      logexit("accept");
    }

    char caddrstr[BUFSZ];
    addrtostr(caddr, caddrstr, BUFSZ);
    printf("[log] connection from %s \n", caddrstr);

    char buf[BUFSZ];
    memset(buf,0,BUFSZ);
    size_t count = recv(csock, buf, BUFSZ -1, 0);//numero bytes recebidos

    printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf); //limitatr mil bytes .1000
    sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
    count = send(csock, buf, strlen(buf)+1,0);
    if (count != strlen(buf)+1){
      logexit("send");
    }
    close(csock);
  }


  exit(EXIT_SUCCESS);

}
