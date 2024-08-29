/*Faça um algoritmo que leia 3 valores a, b e c, coeficientes de uma equação
 de segundo grau, e verifique se a equação tem raízes reais. Se a equação 
 tiver raízes reais, calcule e escreva as raízes da equação. Se não tiver, escreva 
 "A equação não possui raízes reais". Dica: As raízes de uma equação podem ser calculadas 
 pela fórmula de Baskhara. Uma equação não possui raízes se reais se B*B-4*a*c < 0*/

#include <stdio.h>
#include <math.h>

int main() {

float a, b, c, raiz1, raiz2, delta;

printf("Escreva o valor de a: ");
scanf("%f", &a);

printf("Escreva o valor de b: ");
scanf("%f", &b);

printf("Escreva o valor de c: ");
scanf("%f", &c);

delta = (b*b) -4 * a* c;

if (delta < 0) {
    printf("A equação não possui Raizes Reais");
}
else {
    raiz1 = (-b + sqrt(delta))/ (2*a);
    raiz2 = (-b - sqrt(delta))/ (2*a);
    printf("As raízes 1 e 2 da equação são respectivamente: %.1f e %.1f", raiz1, raiz2);
}

return 0;
}
