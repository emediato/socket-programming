/*

MÔNICA EMEDIATO MENDES DE OLIVEIRA
#The server’s job is to set up a communication endpoint and passively wait for a connection from the client. There are four general
#steps for basic TCP server communication:

#-----------------------------------
#1. Create a TCP socket using socket().
#We convert the port number from string to numeric value using atoi(); if the first argu-
#ment is not a number, atoi() will return 0, which will cause an error later when we call
#bind().
#On the server, we need to associate our server socket with an address and port number
#so that client connections get to the right place. Since we are writing for IPv4, we use
#a sockaddr_in structure for this. Because we don’t much care which address we are
#on (any one assigned to the machine the server is running on will be OK), we let the
#system pick it by specifying the wildcard address inaddr_any as our desired Internet
#address. (This is usually the right thing to do for servers, and it saves the server from
#having to find out any actual Internet address.) Before setting both address and port
#number in the sockaddr_in, we convert each to network byte order using htonl() and
#htons().

#-----------------------------------
#2. Assign a port number to the socket with bind().
#As noted above, the server’s socket needs to be associated with a local address and
#port; the function that accomplishes this is bind(). Notice that while the client has to
#supply the server’s address to connect(), the server has to specify its own address to
#bind(). It is this piece of information (i.e., the server’s address and port) that they have
#to agree on to communicate; neither one really needs to know the client’s address. Note
#that bind() may fail for various reasons; one of the most important is that some other
#socket is already bound to the specified port
#-----------------------------------
#3. Tell the system to allow connections to be made to that port, using listen().
#The listen() call tells the TCP implementation to allow incoming connections from
#clients. Before the call to listen(), any incoming connection requests to the socket’s
#address would be silently rejected—that is, the connect() would fail at the client.

#-----------------------------------
#4. Repeatedly do the following:
#• Call accept() to get a new socket for each client connection.
#• Communicate with the client via that new socket using send() and recv().
#• Close the client connection using close().


gcc -g -o servidorTCP servidor.c
.\servidorTCP

SEM argumentos


*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>

//definições para programa

#define MAX 80
#define PORTA_SOCKET_SERVER 8080
#define SA struct sockaddr // Server address

//mensagens entre cliente e servidor


void upperString(char s[]) {
   int c = 0;

   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}


void reverseString(char* str)
{
    int j, i;
    char *ponteirocomeco, *ponteirofim, ch;

    j = strlen(str);
    //aponta as variaveis para o inicio
    ponteirocomeco = str;
    ponteirofim = str;

    // Move ponteirofim p ultimo caracter
    for (i = 0; i < j - 1; i++)
        ponteirofim++;
    //troca do inicio para o fim
    for (i = 0; i < j / 2; i++) {
        // muda caracter
        ch = *ponteirofim;
        *ponteirofim = *ponteirocomeco;
        *ponteirocomeco = ch;
        //atualiza posicao
        ponteirocomeco++;
        ponteirofim--;
    }
}

void aux(int serverSocket)
{
    char buff[MAX];
  //    char response[MAX];

    int n;
      // infinite loop for chat
    for (;;) {
        //uma funcao que escreve zeros para uma string. serve para zerar o resto da struct.
          bzero(buff, MAX);
  //        bzero(response, MAX);
          // le mensagem vinda do cliente e copia no buffer
          read(serverSocket, buff, sizeof(buff));

          //laço para inverter string
    //      for(int i = (sizeof(buff)) - 1, j = 0; i >= 0; i--, j++){
    //              char c = buff[i];
    //              response[j] = islower(c) ? toupper(c) : tolower(c);
      //    }

          //printa response que possui o conteúdo do cliente invertido
          
          reverseString(buff);
          upperString(buff);

          printf("From client: %s\t To client : ", buff);

      //    printf("INVERTIDA! From client: %s\t To client : ", response);


          bzero(buff, MAX);

          n = 0;
          // copia mensagem do servidor no buffer
    //      while ((response[n++] = getchar()) != '\n')
          while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client

      //    write(serverSocket, response, sizeof(buff));
          write(serverSocket, buff, sizeof(buff));

        }
    }

// Driver function
int main()
{
    int serverSocket, clientSocket, read_size;
    struct sockaddr_in servaddr, cli;

    //Tenta criar socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);// AF_INET --> IPv4, SOCK_STREAM --> TCP

    if (serverSocket == -1) {
        printf("\n[TCP Server] Socket error...\n");
        exit(0);
    }
    else
        printf("[TCP Server]Socket created...\n");
    bzero(&servaddr, sizeof(servaddr));


//  Prepara a estrutura de socket do servidor (contendo configurações do socket, como protocolo IPv4, porta de comunicacao e
//filtro de ips que podem se conectar)

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORTA_SOCKET_SERVER);



    // Tenta fazer Bind (informa que o referido socket operara na porta definida por PORTA_SOCKET_SERVER)
    // Binding newly created socket to given IP and verification
    if ((bind(serverSocket, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("[TCP Server] Bind Error\n");
        exit(0);
    }
    else
        printf("[TCP Server]Socket successfully binded..\n");

    // Faz o Listen. É permitido apenas uma conexao no socket
    if ((listen(serverSocket, 5)) != 0) {  //Esta funcao faz com que um socket aguarde por conexoes
        printf("[TCP Server]Listen failed\n");
        exit(0);
    }
    else
        printf("[TCP Server]Server listening\n"); // Aguarda uma conexao
    read_size = sizeof(cli);

    // Estabelece conexoes em um socket. Ela cria um novo socket com as mesmas
//propriedades do socket anterior do seu programa e aloca um novo "int socket"
//para a nova conexao
    clientSocket = accept(serverSocket, (SA*)&cli, &read_size);

    //foi recebido um pedido de conexao. Verifica se o pedido foi bem sucedido

    if (clientSocket < 0) {

        printf("[TCP Server]server acccept failed...\n");
        exit(0);
    }
    else
        printf("[TCP Server] Client Connected!\n\n");


//client se desconectou. O programa sera encerrado.
/*
    if(read_size == 0)
    {
    puts("Cliente desconectado. A aplicacao sera encerrada.");
    fflush(stdout);
                   close(serverSocket);   //fecha o socket utilizado, disponibilizando a porta para outras aplicacoes
    }
    else if(read_size == -1)  //caso haja falha na recepção, o programa sera encerrado
    {
    perror("recv failed");
    }
*/



    // Function for chatting between client and server
    while(1){
        aux(clientSocket);
    }
    // After chatting close the socket
    close(serverSocket);
}
