#include <stdio.h>

#define MASK 0b10000000000000000000000000000000

int sizeBits(int num) {
    int count = 0;
    while ( num != 0 ) {
        count++;
        num >>= 1;
    }
    return count;
}

int printFor(int num) {
    float bitsNumber = (float)sizeBits(num)/4;
    if ((bitsNumber != (int)bitsNumber)){
        bitsNumber++;
    }
    return bitsNumber = (int)bitsNumber * 4;
}

void printBin(int vet[], int num) {
    int aux = printFor(num);
    for(int i = 0; i < aux ; i++) {
        if(vet[i] == 1){
            printf("%d", 1);
        }
        else {
            printf("%d", 0);
        }
    }
}

void shift_left(unsigned int num) {
    int num2 = num;
    int num3 = num;
    //int MASK  = 0b1;
    int count1 = 0;
    int count0 = 0;
    int size = 32;
    for (int i = 0; i < size; i++){
        if(num2 & MASK){
            count1++;
        }
        else {
            count0++;
        }
        num2 <<= 1;
    }
    int aux1[count1];
    int aux0[count0];
    int cont1 = 0;
    int cont0 = 0;
    for (int i = 0; i < size; i++) {
        if (num & MASK) { // se o bit for 1, 
            //adiciona no vetor de 1 se o valor for 1
            aux1[cont1] = 1;
            cont1++;
        } else { // se o bit for 0,
            //adiciona no vetor de 0 o valor 0
            aux0[cont0] = 0;
            cont0++;
        }
        num <<= 1; // desloca os bits para a esquerda
    }
    //junta os dois vetores pegando o  de 1 primeiro e depois o de 0
    int vet[size];
    int i = 0;
    for (i = 0; i < count1; i++){
        vet[i] = aux1[i]; 
    }

    int j = 0;
    for( i = count1; i < size; i++){
        vet[i] = aux0[j];
        j++;
    }
    printBin(vet, num3);

    
}

int main() {
    unsigned int num;
    scanf("%d", &num);
    shift_left(num);
    return 0;
}
