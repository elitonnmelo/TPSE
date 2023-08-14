#include <stdio.h>

#define CHECK_DECIMAL(number) (((number) >= 0 && (number) <=9) ? 1 : 0)

int main (){
    double number = 2;
    if (CHECK_DECIMAL(number)){
        printf("DECIMAL");
    }else {
        printf("NAO DECIMAL");
    }
    return 0;
}