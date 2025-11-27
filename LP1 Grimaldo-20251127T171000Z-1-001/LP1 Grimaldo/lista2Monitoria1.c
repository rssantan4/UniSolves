/* Faça um programa em C que:
• Aloque dinamicamente um array de 5 números inteiros;
• Peça para o usuário digitar os 5 números no espaço alocado;
• Mostre os 5 números alocados na tela;
• Libere a memória alocada*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = NULL;
    int tam = 5; 

    /* alocando */
    ptr = (int *)malloc(tam * sizeof(int));
     
    /* verifica se alocou */
    if(ptr == NULL)
    {
        printf("\nErro ao alocar memória. ");
        exit(1); 
    }

    /* preencher array criado por malloc */
    printf("\nInforme (%d) números inteiros: ", tam);
    for(int i = 0; i < tam; i++){
    printf("\nNúmero (%d): ", tam);
    scanf("%d", &ptr[i]); 
    }
    for(int i = 0; i < 5; i++){
    printf("Números digitados: %d\n", ptr[i]); 
}
    free(ptr);
    return 0;
}