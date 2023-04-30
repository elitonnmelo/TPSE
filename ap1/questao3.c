/*
#include <stdio.h>
#include <stdbool.h>

int countBits(bool w, unsigned int value) {
    unsigned int mask = ((w == 1)? 0x0 : 0x1);
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (value ^ mask) {
            count++;
        }
        value >>= 1;
       
    }
    return count;
}



int main() {
    int num;
    int num2;
    scanf("%d%d", &num, &num2);
    int num3 = countBits(num, num2); 
    printf("%d\n", num3);

    return 0;
}
*/

#include <stdio.h>
#include <stdbool.h>

int countBits(bool w, unsigned int value) {
    //unsigned int mask = ((w == 0)? 0x0 : 0x1);
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (w){
            count += (value & 1) ? 1 : 0;
            value >>= 1;
            continue;
        }else{
            count += (value & 1) ? 0 : 1;
            value >>= 1;
        }
    }
    return count;
}



int main() {
    int num;
    int num2;
    scanf("%d%d", &num, &num2);
    int num3 = countBits(num, num2); 
    printf("%d\n", num3);

    return 0;
}
