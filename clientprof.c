#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

void usage (int argc, char **argv){
  printf("usage: %s <v4|v6> <server port\n>", argv[0]);
  printf ("example: %s 127.0.0.1 51511\n", argv[0]);
  exit(EXIT_FAILURE);
}


#define BUFSZ 1024

int main(int argc, char** argv) {
  if (argc < 3 ){
    usage(argc, argv);
  }

  struct sockaddr_storage storage;
  if ( 0 != addrparse (argv[1], argv[2], &storage)){
    usage(argc, argv);
  }

  int s; //socket
  s = socket (storage.ss_family, SOCK_STREAM,0);
  if (s == -1 ){
    logexit("socket");
  }

  struct sockaddr *addr = (struct sockaddr *)(&storage); //cast
  if(0 != connect(s, addr, sizeof(storage))){ //qual o tamaho efetivo desse pedaço de memoria
    logexit("connect");
  }
  char addrstr[BUFSZ];
  addrtostr(addr, addrstr, BUFSZ);

  printf("connected to %s\n", addrstr);
  //comunicacao cliente servidorTCP
  char buf[BUFSZ];
  memset(buf,0, BUFSZ); //inicializacao com 0

  printf("mensagem: ");
  fgets(buf, BUFSZ-1, stdin);
  size_t count = send(s, buf, strlen(buf)+1, 0); //qual o numero de bytes que efetivamente foi transmitido
  if (count != strlen(buf)+1){
    logexit("send");
  }

  memset(buf, 0, BUFSZ);
  unsigned total = 0 ; //total bytes recebidos
  while(1) {
    count = recv(s, buf + total, BUFSZ - total, 0);
    if (count == 0) {
      break;
    }
    total += count;
  }
  close(s);

  printf("received %d bytes \n", total);
  puts(buf);

  exit(EXIT_SUCCESS);

}
