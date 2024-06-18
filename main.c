#include <stdio.h>

#include "forks.h"
#include "forks_pipes.h"
#include "shared_memory.h"
#include "threads.h"
#include "thread_mutex.h"
#include "threads_semaphores.h"

int main() {
    printf("********** Ejercicio 1: Forks **********\n");
    forks();
    printf("\n\n\n\n********** Ejercicio 2: Forks & Pipes **********\n");
    forks_pipes();
    printf("\n\n\n\n********** Ejercicio 3: Memoria Compartida **********\n");
    shared_memory();
    printf("\n\n\n\n********** Ejercicio 4: Threads & Problemas de Sincronización **********\n");
    threads();
    printf("\n\n\n\n********** Ejercicio 5: Threads & Mutex **********\n");
    thread_mutex();
    printf("\n\n\n\n********** Ejercicio 6: Threads & Semaphores **********\n");
    thread_semaphores();
    return 0;
}

