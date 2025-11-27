/*Questão: Dado dois vetores de inteiros e seus respectivos tamanhos, 
retorne quantos elementos aparecem em ambos vetores*/

#include <stdio.h>
#include <stdlib.h>

int f(int *v1, int *v2, int n1, int n2){
    int cont = 0;

    for(int i = 0; i < n1; i++){
        for (int j = 0; j < n2; j++){
            if(v1[i] == v2[j]){
                cont++;
                break;
            }
        }
    }
    return cont;
}

int main(void){
    int v1[] = {1, 2, 3, 4};
    int v2[] = {3, 4, 5, 6};
    int n1 = sizeof(v1) / sizeof(v1[0]);
    int n2 = sizeof(v2) / sizeof(v2[0]);

    int comuns = elementos_comuns(v1, v2, n1, n2);
    printf("Quantidade de elementos em comum: %d\n", comuns);
    return 0;
}





