/*Escrever um algoritmo que lê um vetor V[10] e o escreve.
Conte, a seguir, quantos valores de V são negativos e escreva esta 
informação.*/

#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

int v[10];
int i, contador;

contador = 0;

for (i = 0; i < 10; i++) {
    printf("Escreva os numeros do vetor: \n");
    scanf("%d", &v[i]);
    fflush(stdin);
}
for (i = 0; i < 10; i++) {
        if (v[i] < 0) {
            contador++;
        }
}
printf("\nEsses são os valores do vetor: \n");
for (i = 0; i < 10; i++) {
        printf("%d ", v[i]);
}
printf("\nEsses são os numeros negativos do vetor: %d \n", contador);
}


