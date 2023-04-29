/*#include <stdio.h>

void shift_left(unsigned int num, int size) {
    unsigned int mask = 1 << (size - 1);
    unsigned int result = 0;
    
    for (int i = 0; i < size; i++) {
        if (num & mask) { // verifica se o bit mais significativo é 1
            result |= 1 << (size - 1 - i); // adiciona o bit extraído à variável de resultado
        }
        num <<= 1; // desloca o número para a esquerda em 1 bit
    }
    
    printf("%d", result);
}

int main() {
    unsigned int num = 0b01010110;
    int size = 8;
    shift_left(num, size);
    return 0;
}*/

#include <stdio.h>

#define MASK 0b10000000000000000000000000000000

void shift_left(unsigned int num) {
    int num2 = num;
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

    for (int it = 0; it < size; it++){
        printf("%d", vet[it]);
    }
    
}

int main() {
    //unsigned int num = 0b01010110;
    unsigned int num;
    scanf("%d", &num);
    //int size = 8;
    shift_left(num);
    return 0;
}
