#include "threads_semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS_3 2
#define ITERATIONS_3 1000000

int counter_3 = 0;

sem_t *semaphore;

void *thread_function_3(void *arg) {
    const int tid = *(int *) arg;
    for (int i = 0; i < ITERATIONS_3; ++i) {
        // Antes de cualquier cosa tengo que bloquear el mutex, así no interfiero con los demás threads
        sem_wait(semaphore);
        counter_3++;
        // Cuando termino de ejecutar mi código puedo desbloquear el mutex para permitir a otros threads ejecutar
        sem_post(semaphore);
    }
    printf("Soy el thread %d y terminé de ejecutar.\n", tid);
    // Como thread llamo a esta función para terminar mi ejecución
    pthread_exit(NULL);
}

void thread_semaphores() {
    if ((semaphore = sem_open("/semaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Declaro un arreglo para almacenar todos mis threads
    pthread_t threads[NUM_THREADS_3];
    int thread_args[NUM_THREADS_3];

    // Creo mis threads
    for (int i = 0; i < NUM_THREADS_3; ++i) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function_3, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Ahora como proceso padre tengo que esperar a que mis threads terminen de ejecutar
    // Para eso voy a iterar mi arreglo de threads y llamar la función pthread_join para esperara a los threads
    for (int i = 0; i < NUM_THREADS_3; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Imprimo el valor final del contador
    printf("Valor final del contador: %d\n", counter_3);

    // Elimino el semaforo para evitar leaks de memoria
    if (sem_close(semaphore) == -1) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
    // Como tengo un semaforo con nombre lo tengo que deslinkear
    if (sem_unlink("/semaphore") == -1) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }
}


