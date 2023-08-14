#include <stdio.h>

int countBits(int num) {
    int count = 0;
    while ( num != 0) {
        if ( num & 1) {
            count++;
        }
        num >>= 1;
    }
    return count;
}
int main(){
     int num = 5;
    printf("O numero de bits definidos em %d e: %d\n", num, countBits(num));
    return 0;
}