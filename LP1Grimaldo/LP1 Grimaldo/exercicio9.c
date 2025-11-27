/*Escreva um algoritmo em C que leia uma série de números inteiros 
(a entrada termina quando o número 0 é digitado) e exiba a soma desses números.*/

#include <stdio.h>

int main()
{
    
    int num, soma;

while(1) {
    printf("Digite uma sequência de números para somar (caso digitar zero, parará a execução)\n");
    scanf("%d", &num);
    if (num == 0) {
        printf("Encerrando o programa. . .");
        break;
    }
    soma += num;
    
    printf("A soma atual está em: %d\n", soma);
}

}