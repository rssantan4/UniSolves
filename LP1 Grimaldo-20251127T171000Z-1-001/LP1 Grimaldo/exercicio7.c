/*Escreva um programa em C que leia dois números inteiros e exiba o maior deles. 
Caso sejam iguais, exiba uma mensagem informando que os números são iguais.*/

#include <stdio.h>

int main()
{
    int num1, num2, maior;
    
    printf("Digite o primeiro numero: ");
    scanf("%d", &num1);
    
    printf("Digite o segundo numero: ");
    scanf("%d", &num2);
    
    if (num1 == num2) {
        printf("Os numeros são iguais.");
    }
    else if (num1 > num2) {
        maior = num1;
        printf("O maior número entre os dois é: %d", maior);
    }
    else if (num1 < num2) {
        maior = num2;
        printf("O maior número entre os dois é: %d", maior);
    }
    return 0;
}