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
#include <time.h>
/*** Structure for Linked List ***/

struct Node //4bytes sizeof returns the size of the type in bytes.
{
       char domainName[20];
       char ipAddr[65];
       int count;

};



typedef struct Node *nodePointer;           // nodePointer points to a structure of type linkedList


int main ()
  {

//- adiciona uma informa ̧c ̃ao de hostname e seu ip associado.
//•search <hostname>- procura o hostname dado,  retornando seu ip caso seja encon-trado.
//•link <ip> <porta>
      char function[24], middle[24], port[24];
      printf("Enter add <hostname> <ip>: \n search <hostname> : \nlink <ip> <porta> ");
      scanf("%23s", function);
      scanf("%23s", middle);
      scanf("%23s", port);

//char name[50];
//printf("Enter your full name: ");
//scanf("%[^\n]s",name);

      if(strncmp(function, "add", sizeof(function)) == 0)
        printf("add");

      if(strncmp(function, "search", sizeof(function)) == 0)
        printf("\nsearch");
}
