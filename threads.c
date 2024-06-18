#include "threads.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS_1 2
#define ITERATIONS_1 1000000

int counter_1 = 0;

// Declaro una función la cual contiene el código que el thread va a ejecutar
// void *args es un puntero a una dirección de memoria que contiene CUALQUIER COSA que yo quiera pasarle al thread
// Puedo pasarle una estructura de datos al thread con información pertinente para ejecutar o puedo simplemente pasar un ID
void *thread_function_1(void *arg) {
    const int tid = *(int *) arg;
    for (int i = 0; i < ITERATIONS_1; ++i) {
        counter_1++;
    }
    printf("Soy el thread %d y terminé de ejecutar.\n", tid);
    // Como thread llamo a esta función para terminar mi ejecución
    pthread_exit(NULL);
}

void threads() {
    // Declaro un arreglo para almacenar todos mis threads
    pthread_t threads[NUM_THREADS_1];
    int thread_args[NUM_THREADS_1];

    // Creo mis threads
    for (int i = 0; i < NUM_THREADS_1; ++i) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function_1, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Ahora como proceso padre tengo que esperar a que mis threads terminen de ejecutar
    // Para eso voy a iterar mi arreglo de threads y llamar la función pthread_join para esperara a los threads
    for (int i = 0; i < NUM_THREADS_1; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Imprimo el valor final del contador
    printf("Valor final del contador: %d\n", counter_1);
}

