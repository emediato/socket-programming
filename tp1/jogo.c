#include <stdio.h>
#include <string.h>


int main() {
  char palavra[10], tentativa[10], copiapalavra[10], arrayposicao[10];
  int i, fim=0, encontrei, auxarrayposicao;
  int n_tentativas=0, limite_tentativas, corretas=0;
  char chute, c;
  //busca palavra
  strcpy(palavra, "momox");
  strcpy(copiapalavra, palavra);
  //limite n_tentativas
  limite_tentativas = strlen(palavra);

  //armazena string com espacos com tamanho da palavra sorteada
  for (i=0; i<strlen(palavra); i++)
    tentativa[i]= ' ';

  printf("\n FORCA EM C \n");
  printf("____________________\n\n");
  do {

    /* apresenta posiçoes ja encontradas */
    for (i=0; i<strlen(palavra); i++)
      printf("%c", tentativa[i]);
    printf("\n");

    /* apresenta posiçoes para letras
    for (i=0; i<strlen(palavra); i++)
      printf("_ ");
    printf("\n");
 */
    printf("Restantes: %d", limite_tentativas - n_tentativas);
    printf(" - Corretas:%d ", corretas);


    printf("\n\nEntre com uma letra:");
    scanf("%c", &chute);
    scanf("%c", &c);

    /*testa se a letra informada encontra-se na palavra escolhida*/
    encontrei =0;
    auxarrayposicao = 0;
    for (i=0; i<strlen(palavra); i++)
      if (copiapalavra[i] == chute){
        copiapalavra[i] = '*';
        tentativa[i] = chute;
        corretas++;
        encontrei = 1;
        arrayposicao[auxarrayposicao] = i;
        auxarrayposicao++;
        //printf ("%d", i);
      }
    if (encontrei == 0 )
      n_tentativas++;

    if ((n_tentativas >= limite_tentativas) || (corretas == strlen(palavra) || chute == '*'))
      fim=1;
  } while( fim == 0);

  return 0;

}
