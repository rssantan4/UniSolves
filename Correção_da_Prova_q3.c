#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");

int A[10], B[10], i, somaA, somaB, maior;

for(i=0;i<10;i++){
    printf("Digite o %dº valor do vetor A: ", i+1);
    scanf("%d", &A[i]);
}
for(i=0;i<10;i++){
    printf("Digite o %dº valor do vetor B: ", i+1);
    scanf("%d", &B[i]);
}
for(i=0;i<10;i++){
    somaA += A[i];
}
for(i=0;i<10;i++){
    somaB += B[i];
}
if(somaA==somaB){
    printf("Os vetores são iguais.");
}else if(somaA>somaB){
    printf("O vetor A têm a soma de seus valores maior do que vetor B.");
}else{
    printf("O vetor B têm a soma de seus valores maior do que vetor A.");
}
}


