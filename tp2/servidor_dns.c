/*
SERVER A
MÔNICA EMEDIATO MENDES DE OLIVEIRA

CODIGO SOLICITA ARGUMENTOS

 ./servidor 8080

 A->B
 A->C

 B->C

 #ip fixo 127.0.0.q
 #porta fixo


 O comando link serve pra adicionar o servidor dado para uma lista de
 onde procurar um hostname caso não exista no servidor original. O comando add
 só deve funcionar localmente, não pode ser possível adicionar um hostname/ip
 em um servidor adicionado utilizando o link.

 printf("Digite as coordenadas X e Y do ponto de origem:\n");
 scanf("%f", &p.x);
 scanf("%f", &p.y);
 printf("Digite o raio de interesse:\n");
 scanf("%f", &r);
 printf("Os pontos mais proximos sao:\n");
 for (i = 0; i < n; ++i) {
   if (Dist(p, v[i]) <= r) {
     printf("(%.1f, %.1f)\n", v[i].x, v[i].y);
   }
 }
}
*/
#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_THREADS 6
#define MAX_LINE 256
#define BUFSZ 256

//*************     FUNCTION PROTOTYPE      *******************//

void DieWithError(char *errorMessage);

void HandleUDPClient(int, char ip[], struct sockaddr_in6, unsigned long);

/*** Structure for Documenting last served client ***/
struct{
    char ipAddress[16];
    time_t timeStamp;
} clientNode;

/*** Structure for Linked List ***/
struct Node{
    char domainName[20];
    int count;
    char ipAddr[65];
    struct Node *next;
}l;                                         // Structure variable "l"


void* handle_request(void *req){
	    Request *request = (Request*)req;
      char packet_str[BUFSZ];
    	strcpy(packet_str, request->buf);

      char buf[BUFSZ];
      struct PacketDNS& packet;
      packet.connection_id = 0;


      packet.connection_id = insert_thread();

      int nBytes,i,j;
      i=10;
      printf("[SERVER] Waiting for messages...\n\n");

      pthread_mutex_lock(&lock);
// Lock the mutex
//       ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        //struct sockaddr *src_addr, socklen_t *addrlen);
      j = buf[0] - '0'; //type
      i = i-j;
      sprintf(buf, "%d", i);
      sendto(cdata->csock, buf, nBytes, 0, (struct sockaddr *) &caddr, size);
      pthread_mutex_unlock(&lock);
      /*laço principal recebe linhas de texto e processa os dados*/
//          while(len = recv(sock, buf, sizeof(buf), 0))  {
    //  }
//
      close(cdata->csock);
      pthread_exit(EXIT_SUCCESS);
}
typedef struct Node *nodePointer;           // nodePointer points to a structure of type linkedList


int main(int argc, char** argv) {
      int udpSocket; //, *port;
      //socklen_t size;
      //char buffer[MAX_LINE];
      struct sockaddr_in6 serverAddr, nohAddr;

      /* Checking the arguments */
      if(argc != 2) {
        printf("\n[SERVER] Argument error.\n\n");
        exit(1);
      }

      /* Creating UDP socket */
      udpSocket = socket(AF_INET6, SOCK_DGRAM, 0);  // AF_INET--> IPv4, SOCK_DGRAM --> UDP

      if (udpSocket == -1) {
            printf("\n[SERVER] Socket error.\n\n");
            exit(1);
      }

      memset(&serverAddr, 0, sizeof(serverAddr)); // For compatibility
      memset(&nohAddr, 0, sizeof(nohAddr)); // For compatibility

      /* Configure settings in address struct */
      serverAddr.sin6_family = AF_INET6;            // IPv6 aceita ipv4
      serverAddr.sin6_addr = in6addr_any;    // Any IP address for the server
      serverAddr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument

      //memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero);
    //search
      /* Bind socket with address struct */
      if( bind(udpSocket, (const struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
          printf("\n[SERVER] Bind Error\n\n");
          exit(1);
      }

      pthread_t sniffer_thread[MAX_THREADS];

      while(1) {
          struct Request *request = (Request*)malloc(sizeof(Request));
          request->fromlen = sizeof(struct sockaddr_in6);

          nBytes = recvfrom(cdata->csock, buf, 128, 0, (struct sockaddr *) &caddr, &size);
          if(nBytes < 0)
      			printf("recvfrom");

          //pthread_mutex_init(&lock, NULL);
          // Initialize mutex

          /* invoke a new thread and pass the recieved request to it */
          if(pthread_create(&sniffer_thread[thread_n], NULL, handle_request, (void*) request) < 0){
                printf("erro ao criar thread");
                return 1; // pthread_exit
          }
          else {
            thread_n++;
          }
     }

     return 0;

}
