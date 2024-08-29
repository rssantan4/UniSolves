/*Faça um algoritmo que leia 3 valores l1, l2 e l3 e verifique
se formam um triângulo e, se formarem, o tipo de triângulo 
formado, escreva: 0 - se não formarem triângulo; 1 - se formarem
um triângulo equilátero (os três lados são iguais); 
2 - se formarem um triângulo isósceles (dois lados iguais e um diferente);
3 - se formarem um triângulo escaleno (3 lados diferentes)*/

#include <stdio.h>
#include <math.h>

int main() {

int l1, l2, l3;

printf("Digite o Primeiro Lado do Triângulo: ");
scanf("%d", &l1);

printf("Digite o Segundo Lado do Triângulo: ");
scanf("%d", &l2);

printf("Digite o Terceiro Lado do Triângulo: ");
scanf("%d", &l3);

if (l1 <= 0 || l2 <= 0 || l3 <= 0 || l1 + l2 <= l3 || l1 + l3 <= l2 || l2 + l3 <= l1) {
    printf(" 0 - Não forma um triangulo.");
}
else {
    if (l1==l2 && l2==l3) {
    printf(" 1 - Este Triângulo é Equilatero.");
}
else if (l1==l2 && l2!=l3) {
    printf(" 2 - Este Triângulo é Isoscele.");
}
else if (l1==l3 && l3!=l2) {
    printf(" 2 - Este Triângulo é Isoscele.");
}
else if (l2==l3 && l1!=l2) {
    printf(" 2 - Este Triângulo é Isoscele.");
}
else if (l1!=l2 && l2!=l3) {
    printf(" 3 - Este Triângulo é Escaleno.");
}

return 0;
}
}
