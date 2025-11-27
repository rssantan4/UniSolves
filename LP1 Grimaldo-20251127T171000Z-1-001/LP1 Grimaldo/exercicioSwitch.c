/*Desenvolva um programa em C que solicite ao usuário a entrada de um número inteiro 
correspondente a um mês do ano (1 para janeiro, 2 para fevereiro, e assim por diante). 
O programa deve então exibir o nome completo do mês correspondente. 
Caso o usuário insira um número fora do intervalo de 1 a 12, 
o programa deve exibir uma mensagem informando que a entrada é inválida.

DESAFIO: Caso o usuário digite 0 o mês corrente deve ser obtido e utilizado
*/

#include <stdio.h>

int main()
{
    int mes, j = 2;
    
    while (j == 2) {
    
    printf("Digite um número inteiro correspondente a um mês do ano: ");
    scanf("%d", &mes);

    switch (mes) {
        case 1:
            printf("Janeiro\n");
            j = 1;
            break;
        case 2:
            printf("Fevereiro\n");
            j = 1;
            break;
        case 3:
            printf("Março\n");
            j = 1;
            break;
        case 4:
            printf("Abril\n");
            j = 1;
            break;
        case 5:
            printf("Maio\n");
            j = 1;
            break;
        case 6:
            printf("Junho\n");
            j = 1;
            break;
        case 7:
            printf("Julho\n");
            j = 1;
            break;
        case 8:
            printf("Agosto\n");
            j = 1;
            break;
        case 9:
            printf("Setembro\n");
            j = 1;
            break;
        case 10:
            printf("Outubro\n");
            j = 1;
            break;
        case 11:
            printf("Novembro\n");
            j = 1;
            break;
        case 12:
            printf("Dezembro\n");
            j = 1;
            break;
        default:
            printf("Valor inválido, escolha outro\n");
    }
    }
    return 0;
}