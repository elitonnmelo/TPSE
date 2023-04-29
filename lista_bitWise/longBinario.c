#include <stdio.h>

void print_bin(int num) {
    for (int i = 0; i < 4; i++) {
        if (num & (1 << i))
            printf("1");
        else
            printf("0");
    }
}

void maskBin(long int num){
    long int mask = 0b1111;
    int group;
    for (int i = 8; i > 0; i--) {
        group = mask & num;
        print_bin(group);
        printf(" ");
        num >>= 4;
    }
}

int main(){
    long int num = 0b11101010;
    maskBin(num);
    return 0;
}