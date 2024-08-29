/*Faça um algoritmo que leia 10 valores, calcule sua média 
e escreva os valores que estão acima da média calculada.*/

#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "");

int v[10], i, acmdia = 0;
float soma, media;

for (i = 0; i < 10; i++) {
    printf("Insira o %dº valor do vetor:\n", i+1);
    scanf("%d", &v[i]);
    fflush(stdin);
}
for ( i = 0; i < 10; i++) {
    soma += v[i];
}
media = (soma/10);
printf("Valores acima da media: ");
for (i = 0; i < 10; i++){
    if (v[i] > media) {
    printf("\n%d ", v[i]);
    acmdia++;
}
}
printf("\nSoma do vetor: %.1f\n", soma);
printf("Media do vetor: %.1f\n", media);
printf("Possuem %d valores do vetor acima da media\n", acmdia);
}


