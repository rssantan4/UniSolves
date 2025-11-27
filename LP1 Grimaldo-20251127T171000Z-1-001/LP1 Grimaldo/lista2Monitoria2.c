/* Faça um programa em C que receba do usuário a quantidade N de números 
a ser digitada. Em seguida, o programa deve alocar dinamicamente um vetor de N 
inteiros, receber N números do usuário e armazenar no vetor, e mostrar o maior valor do 
vetor, o menor valor do vetor e a média dos valores. */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = NULL;
    int n = 0; 
    int maior, menor;
    int soma = 0;
    float media = 0.0;

    printf("Digite a quantidade de numeros a ser digitada: ");
    scanf("%d", &n);
    
    if (n <= 0)
    {
        printf("Quantidade inválida.\n");
        return 1;
    }
    
    /* alocando */
    ptr = (int *)malloc(n * sizeof(int));
     
    /* verifica se alocou */
    if (ptr == NULL)
    {
        printf("\nErro ao alocar memória. ");
        return 1; 
    }

    /* preencher array criado por malloc */
    printf("\nInforme (%d) números inteiros: ", n);

    for (int i = 0; i < n; i++)
    {
    printf("\nNúmero (%d): ", i + 1);
    scanf("%d", &ptr[i]); 
    }
    
    maior = menor = ptr[0];
    
    for (int i = 0; i < n; i++)
    {
        if (ptr[i] > maior)
        {
            maior = ptr[i];
        }
        if (ptr[i] < menor)
        {
            menor = ptr[i];
        }
        soma += ptr[i];
    }
    
    media = soma / n;
        
    printf("Maior numero: %d\n", maior);

    printf("Menor numero: %d\n", menor);
    
    printf("Media: %f\n", media); 

    free(ptr);
    return 0;
}