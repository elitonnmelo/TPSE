#include <stdio.h>

#define gpio_enable (1 << 0)
#define gpio_direction (1 << 1)
#define gpio_level (1 << 2)
#define gpio_rest (1 << 3)

int main() {
    unsigned char gpioREG;
    //A: escreva a logica binaria para setar a variavel gpioREG com habilitado (gpio_enable)
    gpioREG |= gpio_enable;
    //B: escreva a logica binaria para testa se a variavel gpioREG foi definido como saida (gpio_direction), caso positivo voce deve desabilitar (gpio_enabled)
    if (gpioREG & gpio_direction) {
        gpioREG &= ~gpio_enabled;
    }
    //C: escrever a logica binária para setar a variável gpioREG como entrada (gpio_direction).
    gpio &= ~gpio_direction;
    //D: escrever a logica binaria para alterar o gpioREG como nivel alto (gpio_level) ou nivel baixo. Exemplo se ele estava como alto passar para baixo e vice -versa.
    gpioREG ^= gpio_level;  

}