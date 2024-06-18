#include "shared_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

void shared_memory() {
    char buffer[SHM_SIZE];

    // Generamos un ID único para el segmento de memoria compartida
    const key_t key = ftok(".", 'a');

    // Creamos el segmento de memoria compartida
    const int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        printf("Oops, ocurrió un error al crear la memoria compartida\n");
        exit(EXIT_FAILURE);
    }

    // Asignamos la memoria compartida al espacio de memoria del proceso
    // shmat = Shared Memory Attach
    char *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        printf("Oops, ocurrió un error al asignar la memoria compartida\n");
        exit(EXIT_FAILURE);
    }

    const pid_t pid = fork();

    if (pid < 0) {
        printf("Oops, el fork falló\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Soy el proceso hijo y voy a escribir en la memoria compartida\n");

        // Escribir en memoria compartida
        strcpy(shmaddr, "Hola! Soy el proceso hijo!");

        printf("El proceso hijo escribió: %s\n", shmaddr);

        // Eliminamos la memoria compartida del proceso hijo
        // shmdt = Shared Memory Dettach
        if (shmdt(shmaddr) == -1) {
            printf("Oops, ocurrió un error al eliminar la memoria compartida\n");
            exit(EXIT_FAILURE);
        }

        printf("Soy el proceso hijo y terminé mi ejecución.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Soy el proceso padre y voy a esperar a que mi hijo escriba en la memoria compartida...\n");
        // Espero a que mi hijo termine ejecución
        wait(NULL);

        printf("Soy el proceso padre, mis hijos terminaron de ejecutar, ahora voy a leer la memoria compartida...\n");

        // Leer de la memoria compartida
        printf("Soy el proceso padre y leí de la memoria compartida: %s\n", shmaddr);

        // Eliminamos la memoria compartida del proceso padre
        // shmdt = Shared Memory Dettach
        if (shmdt(shmaddr) == -1) {
            printf("Oops, ocurrió un error al eliminar la memoria compartida\n");
            exit(EXIT_FAILURE);
        }

        // Elimino el segmento de memoria compartida
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            printf("Oops, ocurrió un error al eliminar el segmento de memoria compartida\n");
            exit(EXIT_FAILURE);
        }

        printf("Soy el proceso padre y voy a terminar ejecución.\n");
    }
}