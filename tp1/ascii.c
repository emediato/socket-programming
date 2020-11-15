#include <stdio.h>

int main()
{
    int i;

    for( i=0 ; i<=255 ; i++ ) /*ASCII values ranges from 0-255*/
    {
        printf("ASCII value of character %c = %d\n", i, i);
    }

    return 0;
}   
