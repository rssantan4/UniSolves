/*Fazer um programa em C que imprime a tabuada de um número lido do terminal*/

#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    int i, num, tab;

printf("Digite Qualquer Número Inteiro e saiba sua Tabuada\n");
scanf("%d", &num);
printf("Até qual numero de tabuada? ");
scanf("%d", &tab);

for (i = 0; i <= tab; i++) {
printf("%d ", num*i);
}
return 0;
}
