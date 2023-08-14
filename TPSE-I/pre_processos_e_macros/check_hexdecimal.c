#include <stdio.h>
#define CHECK_DECIMAL(number) (((number) >= 0 && (number) <=9) ? 1 : 0)
#define CHECK_HEXDECIMAL(number)  (CHECK_DECIMAL(number) || ((number) >= 'A' && (number) <= 'F' ) || ((number) >= 'a' && (number) <= 'f') ? 1 : 0 )

int main(){
    int number = 'b';
    printf("%d", CHECK_HEXDECIMAL(number));
}