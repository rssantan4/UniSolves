/*Escrever um algoritmo que lê um vetor X[10] e o escreve.
Substitua, a seguir, todos os valores negativos de X pelos seu módulo
e escreva novamente o vetor X.*/

#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

int v[10], i;

for (i = 0; i < 10; i++) {
    printf("Escreva os numeros do vetor: \n");
    scanf("%d", &v[i]);
    fflush(stdin);
}
printf("Esse é o seu vetor em modulo:\n ");
for (i =0; i < 10; i++) {
    if (v[i] < 0) {
        v[i] = v[i] * (-1);
    }
        printf("%d ", v[i]);
}
return 0;
}
