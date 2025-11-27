/*Fazer um programa em C que pergunta um valor em metros e imprime o correspondente 
em decímetros, centímetros e milímetros.*/

#include <stdio.h>

int main()
{
    int num, numdc, numm, numcenti;

    printf("Digite um numero em metros: ");
    scanf("%d", &num);

    numcenti = num * 100;
    numm = num * 1000;
    numdc = num * 10;

    printf("%d - em centímeros: %d - em milimetros: %d - em decimetros: %d. ", num, numcenti, numdc);
}