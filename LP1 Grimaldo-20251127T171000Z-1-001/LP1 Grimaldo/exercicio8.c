/*Faça um programa em C que leia um número inteiro e exiba a tabuada desse número de 1 a 10.*/

#include <stdio.h>

int main()
{
    int i, num, tab;

printf("Digite Qualquer Número Inteiro e saiba sua Tabuada até 10.\n");
scanf("%d", &num);

for (i = 0; i <= 10; i++) {
printf("%d ", num*i);
}
return 0;
}