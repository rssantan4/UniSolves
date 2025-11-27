/*Dada uma variável inteira contagem = 5, use um ponteiro para incrementar 
seu valor em 1 e imprima o valor atualizado.*/

#include <stdio.h>

int main(void)
{
    int contagem = 5;
    int *pNum = &contagem;

    *pNum += 1;

    printf("%d", *pNum);
    return 0;
}