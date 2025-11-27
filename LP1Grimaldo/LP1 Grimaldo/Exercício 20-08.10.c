/*Faça um programa em C que leia uma sequência de números inteiros 
(a sequência termina quando o usuário digitar um número negativo) 
e exiba o maior número digitado.*/

#include <stdio.h>

int main()
{

int num, maior;

maior = -10000;

while(1) {
    printf("Digite uma sequência de números inteiros (caso esse numero for negativo, parará a execução)\n");
    scanf("%d", &num);
    if (num < 0) {
        printf("\nEncerrando o programa. . .\n");
        break;
    }
    
    if (num > maior)
    maior = num;
}
    printf("O maior número digitado foi %d.", maior);

return 0;
}