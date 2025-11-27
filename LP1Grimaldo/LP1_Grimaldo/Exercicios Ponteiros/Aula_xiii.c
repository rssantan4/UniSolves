// Dado um array de caracteres char mensagem[] = "Olá";, 
// use um ponteiro para imprimir cada caractere da string.
#include <stdio.h>
int main(){
char mensagem[] = "Ola" ;
char * msgptr = &mensagem[0];
int c = 0;
while(c < 3){
    printf("%c ", *msgptr++);
    c++;
}
}


// Escreva uma função void multiplicaPorDois(int *arr, int tamanho) que multiplica 
// cada elemento de um array por 2. No main, declare um array int dados[] = {1, 3, 5, 7, 9};, 
// chame a função e imprima o array modificado.

#include <stdio.h>

void multiplicaPorDois(int *arr, int tamanho){
    for(int i = 0; i < tamanho; i++)
    arr[i] *= 2;
}

int main(){

int dados[] = {1, 3, 5, 7, 9};
int * dobraptr = &dados[0];
int c = 0;
multiplicaPorDois(dados, 5);
while(c < 5){
    printf("%d ", *dobraptr++);
    c++;
}
}


// Escreva uma função void reverte(int *arr, int tamanho) que inverte um array. 
// Use-a em int valores[] = {1, 2, 3, 4, 5}; e imprima o array invertido.

#include <stdio.h>

void reverte(int *arr, int tamanho){
    for(int i = tamanho - 1; i >= 0; i--)
    printf("%d ", arr[i]);
}

int main(){
int valores[] = {1, 2, 3, 4, 5};
int tamanho = 5;
    printf("Array invertido: ");
    reverte(valores, tamanho);
}


// Escreva uma função void somaElementos(int *arr, int tamanho) 
// que calcula e imprime a soma dos elementos de um array de inteiros. 
// No main, declare um array int numeros[] = {1, 2, 3, 4, 5, 6, 7};. 
// Chame a função somaElementos passando o sub-array a partir do terceiro elemento 
// (ou seja, &numeros[2]) e o tamanho adequado, para calcular a soma dos elementos a 
// partir do terceiro elemento do array original.


#include <stdio.h>

void somaElementos(int *arr, int tamanho){
    int soma = 0;
    for(int i = 0; i < tamanho; i++){
    soma += arr[i]; 
    }
     printf("Soma dos elementos: %d\n", soma);
}

int main(){
int numeros[] = {1, 2, 3, 4, 5, 6, 7};
int tamanho = 5;

    somaElementos(&numeros[2], tamanho);
    
    return 0;
}


// Desafio 1: Mesclando Dois Arrays Ordenados Usando Ponteiros
// Implemente uma função em C que mescla dois arrays ordenados em um terceiro array, 
// mantendo a ordem. Os arrays são de tamanhos fixos e contêm inteiros em ordem crescente.

// Não use alocação dinâmica de memória; assuma que o terceiro array tem espaço suficiente.
// Use ponteiros para percorrer e mesclar os arrays.

#include <stdio.h>

void mesclar_arrays(const int *arr1, int tamanho1, const int *arr2, int tamanho2, int *mesclado)
{
    int i = 0, j = 0, k = 0;

    // Mescla os dois arrays em ordem crescente
    while (i < tamanho1 && j < tamanho2) {
        if (arr1[i] < arr2[j]) {
            mesclado[k++] = arr1[i++];
        } else {
            mesclado[k++] = arr2[j++];
        }
    }

    // Copia os elementos restantes de arr1, se houver
    while (i < tamanho1) {
        mesclado[k++] = arr1[i++];
    }

    // Copia os elementos restantes de arr2, se houver
    while (j < tamanho2) {
        mesclado[k++] = arr2[j++];
    }
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int mesclado[8];

    mesclar_arrays(arr1, 4, arr2, 4, mesclado);

    printf("Array mesclado: ");
    for (int *ptr = mesclado; ptr < mesclado + 8; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");

    return 0;
}
