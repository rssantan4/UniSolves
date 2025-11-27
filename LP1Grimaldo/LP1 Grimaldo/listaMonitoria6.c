/*Questão 6 Faça uma função em C que: 
 Recebe 3 parâmetros: um vetor de inteiros, um número inteiro n
passado por valor e outro número x passado como ponteiro.
 Retorna um número inteiro. 
 Decompõe o número n em fatores primos e armazena-os nas
posições do vetor. O conteúdo de x deve receber o número de
fatores primos encontrados. Caso o número de fatores encontrados
seja maior que 10, a função deve retornar 1, do contrário deve
retornar 0. 
Dica: Para decompor um número em números primos, deve-se
dividi-lo pelo menor primo possível (restando zero), sucessivamente
até que o quociente seja 1. Ex: 
Assim, a fatoração de 220 é: 2 x 2 x 5 x 11. Logo, o número de
fatores primos encontrados nesse exemplo é 4.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool primo(int num){
    if (num < 2){
        return false;
    }
    for (int i = 2; i < num; i++){
        if (num % i == 0){
            return false;
        }
    }

    return true;
}

int f(int **arr[], int n, int *x){

    int k = 0;
    int div = 2;

    *arr = malloc(sizeof(int));

    while (n > 1) {
        if (primo(div) && n % div == 0) { // Verifica se é primo e divide
        n = n / div;
        *arr = realloc (*arr, sizeof(int) * (k + 1));
        (*vet)[k++] = div;
    }else{
        div++;
    }
}
    *x = k;

return (k > 10) ? 1 : 0;
}

int main(){

    int *arr = NULL, x = 0, n = 0;

    n = 220;

    int retorno = f(&vet, valor, &x);

    printf("fatores primos: ");
    
    for(int i = 0; i < x; i++){
        printf("%d ", arr[i]);
    }
    
    printf("\nx: %d\n", x);
    printf("retorno: %d\n", retorno);


    return 0;

}