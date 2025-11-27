/*Faça um algoritmo em C que leia um número inteiro e determine se ele é par ou ímpar.*/

#include <stdio.h>

int main(){

    int num;

    printf("Digite um número inteiro para exibir se esse número é par ou ímpar.\n");
    scanf("%d", &num);
    
    if(num %2 != 0)
    printf("Número Ímpar.");
    else
    printf("Número Par.");
}