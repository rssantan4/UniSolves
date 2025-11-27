/*Dado um array int numeros[5] = {2, 4, 6, 8, 10};, 
use um ponteiro para imprimir todos os seus elementos.*/

#include <stdio.h>

int main(void)
{
    int numeros[5] = {2, 4, 6, 8, 10};
    int *pNum = numeros;
    
    for(int i = 0; i < 5; i++){
        printf("%d ", *pNum++);
    }

    return 0;
}