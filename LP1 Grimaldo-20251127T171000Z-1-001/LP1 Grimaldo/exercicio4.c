/*Escreva um programa em C que leia um número inteiro e exiba todos os números ímpares de 1 até esse número.*/

#include <stdio.h>

int main()
{
    int num, i;

    printf("Digite um número inteiro para exibir todos os números ímpares até ele.\n");
    scanf("%d", &num);
    
    for (i = 1; i <= num; i++) {
        if(i %2 != 0)
        printf("%d | ", i);
    }
}