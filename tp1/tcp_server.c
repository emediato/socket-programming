/*
MÔNICA EMEDIATO MENDES DE OLIVEIRA
#The server’s job is to set up a communication endpoint and passively wait for a connection from the client. There are four general
#steps for basic TCP server communication:

1 byte = 8 bits

char single byte, capable of holding one character in the local character set

*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFSZ 1024

struct structure1 {
       unsigned char id1; //tipo
       unsigned char id2; //numero d ocorrencias
       unsigned char sizeword; //tamanho palavra
       unsigned char position[]; //array com numero posicoes ocorrencias
};

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
      struct structure1 structprotocol;
      struct sockaddr_in6 serverAddr, clientAddr;
      socklen_t size;

      const char *forca = "momox";
      char buffer[BUFSZ], client_ip[150];
      char armazenaposicao[5]  ;
      char posicoes[] = "";
    //  char find;
      int f;
      f=1;


      //printf("%c", forca[1]);
      int serverSocket, clientSocket, v6only, nBytes;
      uint8_t a = 1;
      uint8_t b, d, j, num1;
      uint8_t num2;
      uint8_t teste = 21;
      j=0;
      num2=strlen(forca);
      structprotocol.sizeword = strlen(forca);
      structprotocol.id1 = a; //inicio servidor tipo 1

      unsigned int protocolo = (concat(structprotocol.id1, structprotocol.sizeword)); //o que preciso enviar para o cliente inicialmente
      sprintf(buffer, "%d", protocolo);

  /* Declaring struct SOCKET! */
  /* Checking the arguments */
      if(argc != 2) {
          printf("\n[TCP Server] Argument error.\n\n");
          exit(1);
      }

  /* Creating TCP socket */
      serverSocket = socket(AF_INET6, SOCK_STREAM, 0);  // AF_INET --> IPv4, SOCK_STREAM --> TCP

      if (serverSocket == -1) {
          printf("\n[TCP Server] Socket error.\n\n");
          exit(1);
      }

  /* socket IPv4 e IPv6 */
      v6only = 0;
      if (setsockopt(serverSocket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0) {
          printf("\n[TCP Server] TIMEOUT - Socket IPv6/IPv4 error.\n\n");
          exit(1);
      }

      memset(&serverAddr, 0, sizeof(serverAddr));   // limpando a estruct

  /* header ----- configure settings in address struct */
      serverAddr.sin6_family = AF_INET6;            // IPv6
      serverAddr.sin6_addr = in6addr_any;    // Any IP address for the server
      serverAddr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument

// ---------------------   memset(&serverAddr, 0, sizeof(serverAddr));   // limpando a estruct
  //memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // For compatibility

  /* Let reusing port */
      int enable = 1;
      if ( 0 != setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))){
          printf("\n[TCP Server] Setsockopt Error\n\n" );
      }

  /* Bind socket with address struct */
      if( bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
            printf("\n[TCP Server] Bind Error\n\n");
            exit(1);
      }
      // If a new client try to connect, ANOTHER socket is created just for it (clientSocket).
          struct sockaddr_storage cstorage; //endereco do cliente
          struct sockaddr *caddr = (struct sockaddr *) (&cstorage);
          socklen_t caddrlen = sizeof(cstorage);
          //--------------------------------------------------------------------
          //  clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &size); // Blocks the execution waiting por clients
          //  clientSocket = accept(serverSocket, caddr, &caddrlen); // Blocks the execution waiting por clients
  /* Initialize size variable to be used later on */
      size = sizeof(struct sockaddr_in6);
      listen(serverSocket, 5); // Transform the socket in an TCP listener, waiting for TCP connections.



      while(1) {
          printf("[TCP Server] Waiting for clients...\n\n");

          clientSocket = accept(serverSocket, caddr, &caddrlen);
          if (clientSocket == -1) { // Test the new socket.
              perror("[TCP Server] Connection Error.\n");
              exit(1);
          }
          getpeername(clientSocket, (struct sockaddr *) &clientAddr, &size);

          if(inet_ntop(AF_INET6, &clientAddr.sin6_addr, client_ip, sizeof(client_ip))) {
              printf("[TCP Server] Client [%s:%d] Connected%d!\n\n", client_ip, ntohs(clientAddr.sin6_port), teste);
            } else {
          }

          //size_t nBytes = send(clientSocket, buffer, strlen(buffer)+1, 0);
          nBytes = write(clientSocket, buffer, BUFSZ);

          //if ( nBytes != (atoi(strlen(buffer)+1))) {
            //printf("\n[TCP Server] Did not send the size of the word to guess.");
          //}
          char c;
          uint16_t aux;
          uint32_t buf;

      while(1) {
          nBytes  = read(clientSocket, buffer, BUFSZ); // Receiving
          //sprintf(&find, "%s", buffer); // Calculates the sum
          //size_t count = recv(clientSocket, &find, BUFSZ - 1, 0); //numero bytes recebidos
          printf("[TCP Server] PALPITE = %s\n", (buffer)+1);
          //printf("[TCP Server] PALPITE!!! ASCII value of character %c = %d\n", (&find)+1, (&find)+1);
          num1 = (buffer[0] - '0'); //1st positin from client
          strcpy(&c, (buffer)+1); //2nd position from client
          printf("%d", num1);


          printf("\n%s", &c);
          if (nBytes<3 || (num1==0) ) {
            printf("[TCP Server]Did not received character from client.");
          } else {
            a=4; //resposta do servidor sera tipo 4
          }

//tipo 3 , numero ocorrencias, posicoes


          //printf("%d", find);
           /*
          for (i=0; i <= (int)structprotocol.sizeword; i++){
              if (forca[i] == f ) {
                printf("Igual %c", forca[1]);
                num2 = num2-1;
                printf("%d", posicoes[i]);
              }
          }

          for (i=0; i <= (int)structprotocol.sizeword; i++){

              if ((forca[i]) == (aux) ) {
                printf("character position:%d", i+1);
                sprintf (armazenaposicao, "%d", i);
                posicoes[j] = i +1;
                structprotocol.position[j] = (unsigned char) i;
                j = j + 1;
                f=1;
                printf("AUXILIAR DO BUFFER FIA %d", aux);
                printf("forca %d", forca[i]);
              }
              if (f==0){
                printf("\ncharacter not found\n");
                structprotocol.id2 = 0; // sem ocorrencias
                i = structprotocol.sizeword;
              }
          }
          structprotocol.id1 = a;///resposta a um palpite
          structprotocol.id2 = j; //numero de ocorrencias
          protocolo = (concat(structprotocol.id1, structprotocol.id2)); //o que preciso enviar para o cliente inicialmente
          sprintf(buffer, "%d", protocolo);

          j=2;
          for (i=0; i<j; i++){
            sprintf(buffer, "%d", posicoes[j]);
          }
    */
          printf("[TCP Server]To aqui %d%d", num2,f);
          if (num2==0){
            sprintf(buffer, "%d", 4);
          }
          a=3; //variable type
          b=2; // ocorrencias
          d=23; //posicoes
          //tipo --------numero de ocorrencias----------posicoes
          aux = concat(a,b);
          aux = concat(aux,d);
          //sprintf(aux,"%d", concat(a,b));
          //sprintf(aux, "%d", a);
        //  strcat(buffer, aux);
          printf("[TCP Server] tentativa A = %d\n", aux);
          strcpy(buf, buf);
          //sprintf(aux, "%d", b);
          //strcat(buffer, b);
        //  printf("[TCP Server] PALPITE = %s\n", buffer);
          //sprintf(aux, "%d", d);
          //strcat(buffer, d);
          //printf("[TCP Server] PALPITE = %s\n", buffer);

          //sprintf(aux, "%d", a);

          nBytes = write(clientSocket, buffer, 128); // Sending back
          if(nBytes <= 0) {
            printf("[TCP Server]Did not send position from server.");
            break;
          }


          //printf("%s\n", find);

        //  switch(buffer[0])	//testa o tipo de mensagem
        //	{
        //		case 2	//mensagem palpite palpite(buffer[1])
        //      write(clientSocket, (buffer[1]), 128); // Sending back
        //    break;
        //		case 3:		//Mensagem de listamento (LIST)
        //		break;
        //		default:		//Caso defaulto
        //		buffer[0] = 1;		//Configura o buffer se saida pra nao mostrar nada e saltar uma linha apenas
        //		break;
        //	}
        //nBytes = read(clientSocket, buffer, 128); // Receiving first number
        /*
          num1 = atoi(buffer);
          if(nBytes < 0 || num1 == 0) break;
            nBytes = read(clientSocket, buffer, 128); // Receiving second number
            num2 = atoi(buffer);
  	      if(nBytes < 0) break;
            sprintf(buffer, "%d", num1+num2); // Calculates the sum
            nBytes = write(clientSocket, buffer, 128); // Sending back
        if(nBytes < 0) break;
          */
        }
        printf("[TCP Server] Client [%s:%d] Connection Closed.\n\n", client_ip, ntohs(clientAddr.sin6_port));
        //printf("[TCP Server] Client [%s:%d] Connection Closed.\n\n", inet_ntoa(clientAddr.sin6_addr), ntohs(clientAddr.sin6_port));
        close(clientSocket); // Releasing the socket for the client

  }
  close(serverSocket);
  return 0;
}
