/*Dado um array de caracteres char mensagem[] = "Olá";
, use um ponteiro para imprimir cada caractere da string.*/

#include <stdio.h>

int main(void)
{
    char mensagem[] = "Ola";
    char *pChar = mensagem;
    
    for(int i = 0; i < 4; i++){
        printf("%c ", *pChar++);
    }

    return 0;
}