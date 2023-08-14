#include <stdio.h>

#define INVERT(number1,number2)\
    int aux = number1;\
    number1  = number2;\
    number2 = aux;
 
 int main(){
    int number1 = 5;
    int number2 = 10;
    INVERT(number1,number2);
    printf("%d \n %d", number1, number2);
 }