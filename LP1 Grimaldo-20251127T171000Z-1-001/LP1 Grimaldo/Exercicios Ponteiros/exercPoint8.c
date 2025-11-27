/*Escreva uma função void converteParaMaiusculas(char *str) 
que altera todas as letras minúsculas de uma string para maiúsculas. 
Teste com a string char texto[] = "Programação";.*/

#include <stdio.h>

void to_upper(char * str)
{
  while (*str != '\0')
  {
    if (*str >= 'a' && *str <= 'z')
      *str -= 32;
    str++;
  }
}

int main(void)
{
  char arr[] = "Programacao";
  to_upper(arr);
  printf("%s", arr);
}