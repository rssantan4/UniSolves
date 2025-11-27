#include <stdio.h>

int main(){

int i, v[20], cont;

for (i = 0; i < 20; i++) {
    printf("Insira o %dº valor: ", i+1);
    scanf("%d", &v[i]);
    fflush(stdin);
}
for (i = 0; i < 20; i++) {
    if (v[i] >= 0 && v[i] <= 100) {
        cont++;
    }
}
printf("%d numero(s) no vetor estão entre 0 e 100", cont);
}

