/*Declare uma variável inteira num com o valor 10. 
Em seguida, declare um ponteiro pNum que aponta para num. 
Imprima o valor de num usando o ponteiro pNum.*/

#include <stdio.h>

int main(void)
{
    int num = 10;
    int *pNum = &num;

    printf("%d", *pNum);
    return 0;
}