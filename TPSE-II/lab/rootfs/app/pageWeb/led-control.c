#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LED_COUNT 4
#define LED_PATH_TEMPLATE "/sys/class/leds/beaglebone:green:usr%d/brightness"

void controlLED(int led, const char *action) {
    char ledPath[100];
    snprintf(ledPath, sizeof(ledPath), LED_PATH_TEMPLATE, led);

    FILE *file = fopen(ledPath, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo do LED.");
        exit(1);
    }

    fprintf(file, "%s", action);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <led> <on/off>\n", argv[0]);
        return 1;
    }

    int led = atoi(argv[1]);
    const char *action = argv[2];

    controlLED(led, action);

    return 0;
}
