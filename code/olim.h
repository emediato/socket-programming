/*
  Arquivo de cabeçalho usado no Protocolo olímpico.
  */


#ifndef OLIM_H
#define OLIM_H

int temp_ms(char *msg); /* função que recebe uma string com o tempo no formato "xxh xxm xxs xxms"
                              e devolve o tempo em milisegundos*/


void insercao (int n, int v[]); /* metódo de ordenação "inserção" */


int pos(int n, int v[]);     /* função que recebe um vetor e um número e retorna a posição desse número*/

int verif_carac(char ch);    /* função que verifica se um caractere é um número ou um espaço*/

int carac_esp(char ch);      /* função que verifica se um caractere é 'h', 'm', 's' ou 'ms'.*/
#endif
