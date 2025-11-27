/*Faça uma função em C que receba duas strings como
parâmetros e verifique se a segunda string ocorre dentro da primeira. Use
aritmética de ponteiros para acessar os caracteres das strings.*/

#include <stdio.h>
#include <stdlib.h>


int doublestring(const char * str1[], const char * str2[]){
    while (*str1 != '\0')
    {
        const char *p1 = str1;
        const char *p2 = str2;
    
    while (*p1 == *p2 && *p2 != '\0') {
            p1++;
            p2++;
        }
        if (*p2 == '\0') {
            return 1;
        }
        str1++;
}
return 0;
}

int main()