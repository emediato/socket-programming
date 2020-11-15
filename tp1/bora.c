#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

unsigned int auxposicao[16];
int posicao[] ;
int quantidade;

void verifica (char *s, char *t){
    int i;
    quantidade = 0;
    char auxposicao[10] = "";
    //printf("%ld", strlen(s));
    printf("ASCII value of character %c = %d\n", (*t), (*t));
    printf("ASCII value of character %c = %d\n", (s[0]), (s[0]));
    //printf("%ld", strlen(s));
  //  int f = (t[0] - '0');
    for (i=0; i <=strlen(s) ; i++) {
      if (s[i] == (*t)) {
        posicao[i] = i;
        quantidade = quantidade + 1;
        }
    }
}

int main() {
    char *pmessage = "momox";
    int s = strlen(pmessage);
    char find;
    int i, cont;
    for (int i = 0; i < s; i++) {
      printf(" _ ");
    }
    printf("Enter any character \n");
    scanf("%c", &find);
    verifica (pmessage, &find);
    printf("%d", quantidade);
    if (quantidade > 0){
      for (i=0; i<quantidade; i++)
        printf("%d", posicao[i]);
    }


}
