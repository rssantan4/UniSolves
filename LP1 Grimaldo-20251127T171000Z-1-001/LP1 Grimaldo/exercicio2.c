/*Faça um programa que implemente um menu onde o usurário deverá selecionar 1 ou 0. 
Caso seja entrado um número diferente, o programa deverá solicitar uma nova opção. [Marcelo Cendron, IFC]*/

#include <stdio.h>
#include <locale.h>

void menu() {
    printf("Menu:\n0-\n1-");
}
int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    int escolha;

   while(1) {
   menu();
   printf("\nEscolha entre 0 ou 1.\n");
   scanf("%d", &escolha);
   if (escolha != 0 && escolha != 1)
   printf("Escolha uma das opções dadas anteriormente.\n");
   else if(escolha == 0 || escolha == 1)
   break;
   }
}