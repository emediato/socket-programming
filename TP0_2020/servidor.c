//SENHA 8 > READ0MSG
//LIST0MSG


#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int serverSocket)
{
    //char buff[MAX];

    char buff[] = "READY";
    write(serverSocket, buff, sizeof(buff));
    int n;
    // infinite loop for chat


    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(serverSocket, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(serverSocket, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main()
{
    int serverSocket, clientSocket, read_size;
    struct sockaddr_in servaddr, cli;

    // try to create socket and verification
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET --> IPv4, SOCK_STREAM --> TCP
    if (serverSocket == -1) {
        printf("[TCP Server] Socket error...\n");
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
    servaddr.sin_port = htons(PORT);

    // Tenta fazer Bind (informa que o referido socket operara na porta definida por PORTA_SOCKET_SERVER)

    // Binding newly created socket to given IP and verification
    if ((bind(serverSocket, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("[TCP Server] Bind Error...\n");
        exit(0);
    }
    else
        printf("[TCP Server]Socket successfully binded..\n");

    // Now server is ready to listen and verification
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

    // Accept the data packet from client and verification
    clientSocket = accept(serverSocket, (SA*)&cli, &read_size);

    //foi recebido um pedido de conexao. Verifica se o pedido foi bem sucedido

    if (clientSocket < 0) {
        printf("[TCP Server]server acccept failed...\n");
        exit(0);
    }
    else
        printf("[TCP Server] Client Connected!\n");

    // Function for chatting between client and server
    func(clientSocket);

    // After chatting close the socket
    close(serverSocket);
}
