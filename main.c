#include <stdio.h>

#include "forks.h"
#include "forks_pipes.h"
#include "shared_memory.h"
#include "threads.h"
#include "thread_mutex.h"
#include "threads_semaphores.h"
#include "signal_handlers.h"

int main() {
    // Bryan - printf("********** Ejercicio 1: Forks **********\n");
    forks();
    // Bryan - printf("\n\n\n\n********** Ejercicio 2: Forks & Pipes **********\n");
    forks_pipes();
    // Bryan - printf("\n\n\n\n********** Ejercicio 3: Memoria Compartida **********\n");
    shared_memory();
    // Bryan - printf("\n\n\n\n********** Ejercicio 4: Threads & Problemas de Sincronización **********\n");
    threads();
    // Bryan - printf("\n\n\n\n********** Ejercicio 5: Threads & Mutex **********\n");
    thread_mutex();
    // Bryan - printf("\n\n\n\n********** Ejercicio 6: Threads & Semaphores **********\n");
    thread_semaphores();
    // Bryan - printf("\n\n\n\n********** Ejercicio 7: Signal Handlers **********\n");
    signal_handler();
    return 0;
}

