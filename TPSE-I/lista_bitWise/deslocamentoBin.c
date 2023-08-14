#include <stdio.h>


void shift_left(int num, int tam) {
    int group = 0;
    for (int i = 0; i < tam; i++) {
        num <<= 1;
        group = (num >> (tam - 1 - i)) & 1; // armazena o bit mais significativo
        //group = (num << i) & (1 << (tam - 1)); // armazena o bit mais significativo
        printf("%d", group);
    }
}
int main(){
    int num = 0b01010110;
    int tamanho = 8;
    shift_left(num, tamanho);
    return 0;
}
