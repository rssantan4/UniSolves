/*Escreva uma função void multiplicaPorDois(int *arr, int tamanho) 
que multiplica cada elemento de um array por 2. 
No main, declare um array int dados[] = {1, 3, 5, 7, 9};, 
chame a função e imprima o array modificado.*/

#include <stdio.h>

void multiplicaPorDois(int *arr, int tamanho)
{
    for(int i = 0; i < tamanho; i++){
        arr[i] *= 2;
    }
}

int main(void)
{
    int dados[] = {1, 3, 5, 7, 9};
    
    multiplicaPorDois(dados, 5);

    for (int i = 0; i < 5; i++) {
        printf("%d ", dados[i]);
    }

    return 0;
}