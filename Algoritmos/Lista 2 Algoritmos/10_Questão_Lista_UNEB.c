/*Faça um algoritmo que leia 3 valores a, b e c, lados de um triangulo, 
e verifique o tipo de triângulo formado escrevendo: 
0 - se o triângulo é retângulo(A^2=B^2+C^2); 
1 - se o triângulo é acutângulo (A^2 > B^2 + C^2) ;
2 - obtusângulo (A^2 < B^2 + C^2). Considere que, para aplicar as relações mostradas, 
algoritmo deve garantir que o maior dos 3 lados estará em A.*/

#include <stdio.h>
#include <math.h>

int main() {

int l1, l2, l3, maior, maior2, menor;

printf("Digite o Primeiro Lado do Triângulo: ");
scanf("%d", &l1);

printf("Digite o Segundo Lado do Triângulo: ");
scanf("%d", &l2);

printf("Digite o Terceiro Lado do Triângulo: ");
scanf("%d", &l3);

if (l1 > l2 && l2 > l3) {
    maior=l1;
    maior2=l2;
    menor=l3;
}
else if (l1 > l3 && l3 > l2) {
    maior=l1;
    maior=l3;
    menor=l2;
}
else if (l2 > l3 && l3 > l1) {
    maior=l2;
    maior2=l3;
    menor=l1;
}
else if (l2 > l1 && l1 > l3) {
    maior=l2;
    maior2=l1;
    menor=l3;
}
else if (l3 > l2 && l2 > l1) {
    maior=l3;
    maior2=l2;
    menor=l1;
}
else if (l3 > l1 && l1 > l2) {
    maior=l3;
    maior2=l1;
    menor=l2;
}

if (pow(maior, 2) == pow(maior2, 2) + pow(menor, 2)) {
    printf("0 - Esse Retângulo é  retângulo.");
}
else if (pow(maior, 2) > pow(maior2, 2) + pow(menor, 2)) {
    printf("1 - Esse triângulo é acutângulo.");
}
else if (pow(maior, 2) < pow(maior2, 2) + pow(menor, 2)) {
    printf("2 - Esse triângulo é obtusângulo.");
}

return 0;

}
