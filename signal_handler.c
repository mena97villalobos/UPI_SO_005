#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "signal_handlers.h"

volatile int stop_signal = 1;

// Aquí creamos un handler para señales esta función es la que vamos a registrar
// Con esta función estamos haciendole override al signal handler del kernel
void my_signal_handler(int signum) {
    printf("\nRecibí la señal SIGINT (^+C)...\n");
    stop_signal = 0;
}

void signal_handler() {
    // Registro el signal handler
    // Noten que estoy utilizando de primer parámetro la señal que quiero manejar con mi función
    if (signal(SIGINT, my_signal_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Registré un signal handler para SIGINT (^+C).\n");

    // Infinite loop to keep the program running
    while (stop_signal) {
        printf("Running...\n");
        sleep(1);
    }
}

void main() {
    signal_handler();
}
