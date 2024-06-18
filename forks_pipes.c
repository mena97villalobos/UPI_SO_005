#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "forks_pipes.h"

void forks_pipes() {
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        printf("Oops, el pipe falló!");
        exit(EXIT_FAILURE);
    }

    const pid_t pid = fork();
    if (pid < 0) {
        printf("Oops, el fork falló\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Corriendo en el proceso hijo

        // Declaro una variable para recibir un mensaje
        pid_t received_message;

        // Cierro la escritura en el pipe
        close(pipe_fd[1]);

        // Leo el mensaje en el pipe
        read(pipe_fd[0], &received_message, sizeof(received_message));

        printf("Soy el proceso hijo, mi pid es: %d\n", received_message);

        // Cierro el lado de lectura del pipe
        close(pipe_fd[0]);

        sleep(5);
        printf("Soy el proceso hijo, terminé ejecución ahora voy a morir\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Soy el proceso padre, mi hijo es: %d\n", pid);

        // Cierro la lectura del pipe
        close(pipe_fd[0]);

        // Escribo mi mensaje en el pipe
        write(pipe_fd[1], &pid, sizeof(pid));

        // Cierro la escritura en el pipe
        close(pipe_fd[1]);

        // Espero a mis hijos
        wait(NULL);
        printf("Mis hijos terminaron ejecución, ahora voy a morir");
    }
}


