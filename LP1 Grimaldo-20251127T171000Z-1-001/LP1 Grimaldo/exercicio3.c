/*As maçãs custam R$ 0,30 cada se forem compradas menos do que uma dúzia, 
e R$ 0,25 se forem compradas pelo menos doze. Escreva um programa que 
leia o número de maçãs compradas, calcule e escreva o valor total da compra. [Marcelo Cendron, IFC]*/

#include <stdio.h>

int main()
{
    float uni, price;

    printf("Quantas Unidads de Maçãs Compradas?\n");
    scanf("%f", &uni);
    
    if (uni < 12)
    price = 0.30;
    else if (uni >= 12)
    price = 0.25;
    
    printf("Valor total da compra de maçãs: %.2f", uni * price);
}