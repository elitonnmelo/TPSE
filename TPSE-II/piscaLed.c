#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LED_COUNT 4  // Quantidade de LEDs disponíveis
#define DELAY_SECONDS 1

// Função para acender um LED
void turn_on_led(int led) {
    char led_path[100];
    snprintf(led_path, sizeof(led_path), "/sys/class/leds/beaglebone:green:usr%d/brightness", led);
    
    FILE* file = fopen(led_path, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo do LED.");
        exit(1);
    }

    fprintf(file, "1");  // Liga o LED
    fclose(file);
}

// Função para apagar um LED
void turn_off_led(int led) {
    char led_path[100];
    snprintf(led_path, sizeof(led_path), "/sys/class/leds/beaglebone:green:usr%d/brightness", led);
    
    FILE* file = fopen(led_path, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo do LED.");
        exit(1);
    }

    fprintf(file, "0");  // Desliga o LED
    fclose(file);
}

int main() {
	int cont = 0;
	while(cont < 4){
	    for (int i = 0; i < LED_COUNT; i++) {
		turn_off_led(i);
		sleep(DELAY_SECONDS);
	    }
	    for (int i = 0; i < LED_COUNT; i++) {
		turn_on_led(i);
		sleep(DELAY_SECONDS);
	    }
	    
	    cont++;
	 }

    return 0;
}

