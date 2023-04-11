#include <stdio.h>

#define DIVISIVEL(number) ( (((number) % 10) == 0 ) ? 1 : 0)
int main (){
    int number = 21;
    if (DIVISIVEL(number)){
        printf("divisivel");
    }else {
        printf("nao divisivel");
    }
    return 0;
}
