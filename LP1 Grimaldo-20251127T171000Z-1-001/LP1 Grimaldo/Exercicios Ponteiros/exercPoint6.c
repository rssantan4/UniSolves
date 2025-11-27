/*Escreva uma função void reverte(int *arr, int tamanho) que inverte um array. 
Use-a em int valores[] = {1, 2, 3, 4, 5}; e imprima o array invertido.*/

#include <stdio.h>

void reverte(int *arr, int tamanho)
{
    for(int i = tamanho - 1; i >= 0; i--){
        printf("%d ", arr[i]);
    }
}

int main(void)
{
    int valores[] = {1, 2, 3, 4, 5};
    
    reverte(valores, 5);

    return 0;
}