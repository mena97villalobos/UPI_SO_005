#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "forks.h"

void forks() {
    const pid_t pid = fork();

    if (pid < 0) {
        printf("Oops, el fork falló\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Corriendo en el proceso hijo
        printf("Soy el proceso hijo\n");
        sleep(5);
        printf("Soy el proceso hijo, terminé ejecución ahora voy a morir\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Soy el proceso padre, mi hijo es: %d\n", pid);
        wait(NULL);
        printf("Mis hijos terminaron ejecución, ahora voy a morir");
    }
}


