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
// char         1 byte
struct structure1 //4bytes sizeof returns the size of the type in bytes.
{
       unsigned char id1; //tipo
       unsigned char id2; //numero d ocorrencias
       unsigned char sizeword; //tamanho palavra
       unsigned char position[]; //array com numero posicoes ocorrencias
};

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

int main ()
  {
      struct structure1 structprotocol;

      const char *ch = "momox";
      unsigned int a = 2; //tipo cliente inicializacao

      structprotocol.id1 = a;
      structprotocol.sizeword = strlen(ch);

      char find;
      printf("Enter any character \n");
      scanf("%c", &find);

      int i, f, count;
      count =0;
      char armazenaposicao[structprotocol.sizeword];
      char s1[structprotocol.sizeword];
      for (i=0; i<structprotocol.sizeword; i++){
        if (ch[i]==find){
          printf("character position:\n%d", i+1);
          sprintf(armazenaposicao, "%d", i);
          strcat(s1, armazenaposicao);
          structprotocol.position[count] = (unsigned char) i;
          count = count + 1;
          f=1;
        }
        if (f==0){
          printf("\ncharacter not found\n");
        }
      }

      structprotocol.id2 = count; //numero de ocorrencias
      //for (i=0; i<count; i++){
        //printf("%u\n", structprotocol.position[i]);
        int c = atoi(s1);
        printf("%d\n", c);
    //  }
      printf("\n teste");


}
