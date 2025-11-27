#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");

int mes[12], i, j, soma, media, credito;
j = 0;
  
  do{
for(i=0;i<12;i++){
    printf("Insira o saldo do %dº mes: \n", i+1);
    scanf("%d", &mes[i]);
    fflush(stdin);
}
for(i=0;i<12;i++){
    soma += mes[i];
}
media = soma/12;

if(media<=2000){
    printf("nenhum crédito.\n");
}else if(media>2000 && media<=5000){
    credito = media*0.15;
    printf("Esse é o seu credito disponivel: %d\n", credito);
}else if(media>=5001){
    credito = media*0.3;
    printf("Esse é o seu credito disponivel: %d\n", credito);
}
printf("Deseja continuar calculando? Digite 1 para continuar e 2 para sair.\n");
scanf("%d", &j);

if(j==2){
    printf("Encerrando o programa.");
}
}while(j!=2);

return 0;
    
}
