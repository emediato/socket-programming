#include <string.h>
#include <stdlib.h>
#include "olim.h"  /*  Arquivo de cabeçalho usado no Protocolo olímpico. */
#include <stdio.h>



/* função que verifica se um caractere é um númeo ou um espaço*/
int verif_carac(char ch) {
	if(ch =='0'||ch =='1'||ch =='2'||ch =='3'||ch =='4'||ch =='5'||ch =='6'||ch =='7'||ch =='8'||ch =='9'||ch ==' ')
            return(1);
        return (0);
}

/* função que verifica se um caractere é 'h', 'm', 's' ou 'ms'.*/
int carac_esp(char ch) {
       if(ch == 'h' || ch == 'm' || ch == 's')
          return (1);
       return (0);
}

/* metódo de ordenação "inserção" */

void insercao (int n, int v[]) {

  /* o vetor  v[0..n-1]  é uma permutação do vetor original  e
   o vetor  v[0..j-1]  está em ordem crescente.*/
   int i, j, x;
   for (j = 1; j < n; ++j) {
      x = v[j];
      for (i = j-1; i >= 0 && v[i] > x; --i) 
         v[i+1] = v[i];
      v[i+1] = x;
   }
}


 /* função que recebe um vetor e um número; retorna a posição desse número*/

int pos(int n, int v[]) {

  int i, j;
  for(i=0; i<1000; i++) { /* procura o primeiro elemento diferente de zero no vetor*/
     if(v[i] != 0) break; /* 'i' é a posição do primeiro elemento maior que zero*/
  }
  for(j=0; j<1000; j++) { /* procura dentro do vetor o elemento recebido na função */
     if(v[j] == n && v[j+1] != n) break; /* 'j' é a posição do elemento requisitado na função*/
                      
   }  
  return((j-i)+1);        /* retorna a posição do elemento requisitado em relação ao primeiro elemento*/

}


/* Esta função recebe uma string com o tempo no formato "xxh xxm xxs xxms"
   e devolve o tempo em milisegundos, desde que ele seja maior que "0ms"*/
int temp_ms(char *msg){
        char str[256]; /* string auxiliar a ser chamada na função "atoi"  */
	int h=0;
        int m=0, s=0, ms=0, i=0, j=0;
        int tempo=0;
        char ch;
        int test=2;
        int testc=0;
        
	
	
	while(msg[i] != '\0'){        /* verifica a string até o final  */
		
	    if(msg[i] == 'h'){        /* procura por hora dentro da string  */
	        strcpy(str, msg);     /* copia a mensagem recebida*/
		for(j=i-1; j>=0; j--) {  /* percorre a string antes do caractere especial de tempo */
                    ch = str[j];
                    test = verif_carac(ch); /* verifica se os caracteres anteriores são números ou espaço*/
                    if(test == 0) str[j] = ' '; /* se o caractere for diferente de ' ' e de número, a string recebe um ' ' */
                    testc = carac_esp(ch); 
                    if(testc>0){           /* se for encontrado um caractere especial de tempo a string é "zerada" até o início*/
                       while(j>=0) {
                          str[j] = ' ';
                          j--;
                       }
                    }
                  }  
                str[i] = '\0';                   /* finaliza a string*/
                h= atoi(str);                    /* valor inteiro é extraído da string*/
            }

	    if(msg[i] == 'm' && msg[i+1] != 's'){ /* procura por minutos  dentro da string  */
            	strcpy(str, msg);                 /* copia a mensagem recebida*/
                for(j=i-1; j>=0; j--) {           /* percorre a string antes do caractere especial de tempo */
                    ch = str[j]; 
                    test = verif_carac(ch);       /* verifica se os caracteres anteriores são números ou espaço*/
                    if(test == 0) str[j] = ' ';  /* se o caractere for diferente de ' ' e de número, a string recebe um ' ' */
                    testc = carac_esp(ch);
                    if(testc>0){                 /* se for encontrado um caractere especial de tempo a string é "zerada" até o início*/
                       while(j>=0) {
                          str[j] = ' ';
                          j--;
                       }
                    }
                  }
                str[i] = '\0';
	        m = atoi(str);                 /* valor inteiro é extraído da string*/
             } 
 
	    if(msg[i] == 's' && msg[i-1] != 'm'){ /* procura por segundos dentro da string  */
                strcpy(str, msg);                 /* copia a mensagem recebida*/
                for(j=i-1; j>=0; j--) {           /* percorre a string antes do caractere especial de tempo */
                    ch = str[j];
                    test = verif_carac(ch);      /* verifica se os caracteres anteriores são números ou espaço*/
                    if(test == 0) str[j] = ' ';  /* se o caractere for diferente de ' ' e de número, a string recebe um ' ' */
                    testc = carac_esp(ch);
                    if(testc>0){                 /* se for encontrado um caractere especial de tempo a string é "zerada" até o início*/
                       while(j>=0) {
                          str[j] = ' ';
                          j--;
                       }
                    }
                  } 
                str[i] = '\0';                   /* finaliza a string*/
                s= atoi(str);                    /* valor inteiro é extraído da string*/
              }


            if(msg[i] == 'm' && msg[i+1] == 's'){ /* procura por milisegundos dentro da string  */
	        strcpy(str, msg);                 /* copia a mensagem recebida*/
		for(j=i-1; j>=0; j--) {           /* percorre a string antes do caractere especial de tempo */
                    ch = str[j];
                    test = verif_carac(ch);       /* verifica se os caracteres anteriores são números ou espaço*/
                    if(test == 0) str[j] = ' ';    /* se o caractere for diferente de ' ' e de número, a string recebe um ' ' */
                    testc = carac_esp(ch);
                    if(testc>0){                   /* se for encontrado um caractere especial de tempo a string é "zerada" até o início*/ 
                       while(j>=0) {
                          str[j] = ' ';
                          j--;
                       }
                    }
                  } 
		str[i] = '\0';                 /* finaliza a string*/
		ms= atoi(str);                 /* valor inteiro é extraído da string*/
             }

            i++;         
        }
        h += h*3600000;
        m += m*60000;
        s += s*1000;
        tempo = h + m +s + ms; /* a variável "tempo" recebe o tempo total em milisegundos */
	return(tempo);
}  




