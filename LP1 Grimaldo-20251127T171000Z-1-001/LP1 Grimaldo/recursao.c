/*Escreva uma função recursiva em C chamada somaDigitos que receba um número
 inteiro positivo n e retorne a soma de seus dígitos. Observe o exemplo

Entrada: 1234
Saída: 10
(Explicação:  1+2+3+4=10)*/

#include <stdio.h>

int somaDigitos(int n) {
    if (n >= 0 && n <= 9) {  
        return n;
    } else {  
        return n % 10 + somaDigitos (n /10);
    }
}

int main() {

    int num = 0;
    
    printf("Digite um numero inteiro positivo:\n");
    scanf("%d", &num);

    printf("Soma de digitos:%d\n", somaDigitos(num));
}