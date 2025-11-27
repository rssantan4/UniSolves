/*Crie um programa em C que leia uma temperatura em graus Celsius e a converta para Fahrenheit. 
O programa deve exibir a mensagem "Frio" se a temperatura em Fahrenheit for menor que 50, 
e "Quente" se for maior ou igual a 50.*/

#include <stdio.h>

int main()
{

float tempc, tempf;

    printf("Digite uma temperatura em Celsius\n");
    scanf("%f", &tempc);
    
    tempf = (1.8 * tempc) + 32;
    
    if (tempf < 50)
    printf("Frio.");
    else if (tempf >= 50)
    printf("Quente.");
}