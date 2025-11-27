/*Crie um algoritmo em C que leia um número inteiro positivo e calcule o fatorial desse número.*/

#include <stdio.h>

int main()
{
    int num, i = 0;
    unsigned long long fatorial = 1;

    printf("Digite um número inteiro para saber o seu respectivo fatorial: a execução)\n");
    scanf("%d", &num);
    
    if (num < 0) {
        printf("\nFatorial não existe para números negativos.\n");
    }
    else {
    for (i = 1; i <= num; ++i) {
            fatorial *= i;  
        }

        printf("O fatorial de %d é: %llu\n", num, fatorial);
    }

    return 0;
}