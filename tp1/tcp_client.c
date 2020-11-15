/*
Mônica Emediato
#Its job is to initiate communication with a server that is passively waiting to be contacted
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#define BUFSZ 1024

// Function to concatenate two integers into one
int concat(int a, int b){
      char s1[10];
      char s2[10];
      // Convert both the integers to string
      sprintf(s1, "%d", a);
      sprintf(s2, "%d", b);
      // Concatenate both strings
      strcat(s1, s2);
      // Convert the concatenated string to integer
      int c = atoi(s1);
      // return the formed integer
      return c;
}


int main(int argc, char** argv) {
    int clientSocket, nBytes;
    char buffer[128];
    unsigned int protocolo, a;
    struct sockaddr_in serverAddr;
    socklen_t size;
    // tipo palpite
    char aux[] = "2";
  //  unsigned char msg;

    /* Checking the arguments */
    if(argc != 3) {
      printf("\n[TCP Client] Argument error.\n\n");
      exit(1);
    }

    /* Create TCP socket */
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET --> IPv4, SOCK_STREAM --> TCP

    if (clientSocket == -1) {
        printf("\n[TCP Client] Socket error.\n\n");
        exit(1);
    }
    memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // for compatibility

    /* Configure settings in address struct */
    serverAddr.sin_family = AF_INET;                 // IPv4
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]); // Get the IP address by the argument
    serverAddr.sin_port = htons(atoi(argv[2]));      // Get the port by the argument


    /* Initialize size variable to be used later on */
    size = sizeof(struct sockaddr_in);

    printf("[TCP Client] Trying to connect to the server...\n");
    // Trying to connect in the TCP Server

    if (connect(clientSocket, (struct sockaddr*) &serverAddr, size) < 0) {
        printf("\n[TCP Client] Connection Error.\n\n");
        exit(1);
    }

    printf("[TCP Client] CONNECTED! Welcome to * * * FORCA * * *. Size of the word is ");
    /* ---------------------------------------------------------
    ---------------------------- FROM HERE WE ARE CONNECTED !!!!
    ------------------------------------------------------------ */
    nBytes = recv(clientSocket, buffer, 128, 0);
    a = buffer[0] - '0';

    if (a==0){
      printf("\n[TCP Client] Did not received size of server ");
    }
    protocolo = atoi(buffer+1); // posicao 1 do buffer esta tamanho da palavra para ser adivinhada
    printf("%u",protocolo);
    for (int i = 0; i < (int)protocolo; i++) {
      printf(" _ ");
    }
    printf("\n[TCP Client] Enter the first PALPITE to begin : ");
    fgets(buffer, BUFSZ, stdin); //le mensagem
    strcat(aux, buffer);
    nBytes = strlen(aux)+1;
      // Sending data, without specifying a destination, because the TCP connection is already made.
      //if(atoi(buffer[0]) == 0) break; //verifica se primeira posicao do buffer eh numero
    //  if((buffer[0]) == 0) break;

  while(1) {
    while(1){
          write(clientSocket, aux, nBytes);

          nBytes = recv(clientSocket, buffer, BUFSZ, 0);
          a = buffer[0] - '0'; //cast pra int
          printf("[TCP Client] Answer received:  %s \n", buffer);

          if ((nBytes < 1)) {
              printf("\n[TCP Client]Nada chegou! ");
          }
          if(a==4){
              break;
          }
          if (a==5) {
              printf("\n[TCP Client] Voce acertou %d vezes em posicoes: %d\n\n", (buffer[1] - '0'), (buffer[2] - '0'));
          }
          sprintf(aux, "%d", 1);
          printf("\n[TCP Client] Enter another palpite: ");
          fgets(buffer, 128, stdin);
          strcat(aux, buffer);
          nBytes = strlen(aux)+1;

          //send(clientSocket, buffer, nBytes, 0);

          //nBytes = recv(clientSocket, buffer, 128, 0);
          //printf("\n[TCP Client] Answer received: %s\n\n", buffer);
        }
  }
   //fim while 1
  printf("\n[TCP Client] Quitting...\n");
  close(clientSocket); // Releasing the socket.
  return 0;
}
