/*
Nome: Mônica Emediato
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "files.h"

// Assinando a função
void *client_handler(void* socket);

int main(int argc, char** argv) {
  int server_socket, client_socket, v6only;
  char client_ip[150];
  unsigned int size;

  /* Declarando a estrutura ! */
  struct sockaddr_in6 server_addr, client_addr;

  /* checando os argumentos */
  if(argc != 2) {
  printf("\n[TCP Server] Argument error.\n\n");
  exit(1);
  }

  /* criando o socket tcp */
  server_socket = socket(AF_INET6, SOCK_STREAM, 0);  // AF_INET6 --> IPv6, SOCK_STREAM --> TCP
  if (server_socket == -1) {
  printf("\n[TCP Server] Socket error.\n\n");
  exit(1);
  }

  /* socket trabalha com IPv4 e IPv6 */
  v6only = 0;
  if (setsockopt(server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0) {
  printf("\n[TCP Server] Socket IPv6/IPv4 error.\n\n");
  exit(1);
  }

  /* Configurando a estrutura de endereços */
  memset(&server_addr, 0, sizeof(server_addr));   // limpando a estruct

  server_addr.sin6_family = AF_INET6;           // IPv6
  server_addr.sin6_addr = in6addr_any;          // servidor recebe qualque endereço IP
  server_addr.sin6_port = htons(atoi(argv[1])); // Capturando o numero de porto pelo primeiro argumento


  /* Bind socket */
  if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
  printf("\n[TCP Server] Bind Error\n\n");
  exit(1);
  }

  /* Inicializar o tamanho da variavel para ser utilizada depois */
  size = sizeof(struct sockaddr_in6);

  listen(server_socket, 5); // Transforma o socket em um ouvinte tcp, esperando por conexões.

  while(1) {
    // Se um novo cliente tenta se conectar, outro socket é criado só para ele (client_socket).


    client_socket = accept(server_socket, NULL, NULL); // espera ocupada por clientes
    if (client_socket < 0) { // testa novo socket.
      perror("[TCP Server] Connection Error.\n");
      exit(1);
    }

    // Conseguindo informaçoes sobre o novo cliente e adicionando no client_ip.
    getpeername(client_socket, (struct sockaddr *) &client_addr, &size);
    inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, sizeof(client_ip));

    pthread_t thread_id;

  if(pthread_create(&thread_id, NULL,  client_handler, (void*) &client_socket) < 0) {
    perror("could not create thread");
    return 1;
  }
  pthread_detach(thread_id); // Não precisa se juntar ao segmento principal depois

  }
  close(server_socket); // liberando o socket do servidor
  return 0;
}

void *client_handler(void* socket) {
  char buffer[128];
  char *bufferb;
  bufferb = (char*) malloc(128*sizeof(char));
  int bytes, socket_id;
  socket_id = *((int*)socket); // transforma em um pointer-to-int e depois recebe ser valor
  begintp();		//inicializa arquivo com usuarios e senhas
  char *tipo = malloc(3*sizeof(char));
  char *nome = malloc(15*sizeof(char));
  char *senha = malloc(15*sizeof(char));
  char *book = malloc(50*sizeof(char));
  char *message = malloc(100*sizeof(char));
  while(1) {
    memset(&buffer, 0, sizeof(buffer));
    bytes = read(socket_id, buffer, 128);		//Recebe comando do cliente

    if(strcmp(buffer, "q") == 0 || bytes < 0) break;



	switch(buffer[0])	//testa o tipo de mensagem
	{
		case 'N':	//Mensagem de cadastro (NEW_USER)
		sscanf(buffer, "%s %s %s", tipo , nome, senha);
		bufferb = new_user(nome,senha);
		break;

		case 'S':		//Mensagem de Envio (SEND)
		sscanf(buffer, "%s %s %s %s %[^\n]s", tipo , nome, senha, book, message);
		bufferb = sendmsgtp(nome, senha, book, message);
		break;

		case 'R':		//Mensagem de leitura (READ)
		sscanf(buffer, "%s %s %s %s", tipo , nome, senha, book);
		bufferb = readmsgtp(nome, senha, book);
		break;

		case 'L':		//Mensagem de listamento (LIST)
		sscanf(buffer, "%s %s %s", tipo , nome, senha);
		bufferb = list(nome, senha);
		break;

    case 'E':		//Mensagem de saída (EXIT)
    bufferb[0] = ' ';		//Configura o buffer se saida pra nao mostrar nada e saltar uma linha apenas
		bufferb[1] = '\0';
    break;

		default:		//Caso defaulto
		bufferb[0] = ' ';		//Configura o buffer se saida pra nao mostrar nada e saltar uma linha apenas
		bufferb[1] = '\0';
		break;

	}

	strcpy(buffer,bufferb);		//Como as funções da biblioteca trabalham com vetores dinâmicos e as locais com estáticos, usamos os dois.
    bytes = send(socket_id, buffer, sizeof(buffer), 0);		//Envia resposta
  }

  close(socket_id);
  return 0;
}
