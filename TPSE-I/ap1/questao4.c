#include <stdio.h>
#include <stdbool.h>


int setBits(bool w, unsigned int i,  unsigned int  j, unsigned int value) {
    if ((i < 0) || (j > 31) || (j < i) ) {
        return -1;
    }
    unsigned int mask = 0b0;
    int it =0;
    while (it <= j){
    
        if (it == i){
            mask += pow(2, i);
            i++;
        }
        it++;
    }
    return value = w ? value |= mask : (value ^ mask) & ~mask;
}
int main() {
    int w, i, j, value;
    scanf("%d%d%d%d", &w, &i, &j, &value);
    int num = setBits(w, i, j, value);
    printf("%d", num);
}