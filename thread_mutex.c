#include "thread_mutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS_2 2
#define ITERATIONS_2 1000000

int counter_2 = 0;
// Un mutex es una forma de sincronizar procesos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Declaro una función la cual contiene el código que el thread va a ejecutar
// void *args es un puntero a una dirección de memoria que contiene CUALQUIER COSA que yo quiera pasarle al thread
// Puedo pasarle una estructura de datos al thread con información pertinente para ejecutar o puedo simplemente pasar un ID
void *thread_function_2(void *arg) {
    const int tid = *(int *) arg;
    for (int i = 0; i < ITERATIONS_2; ++i) {
        // Antes de cualquier cosa tengo que bloquear el mutex, así no interfiero con los demás threads
        pthread_mutex_lock(&mutex);
        counter_2++;
        // Cuando termino de ejecutar mi código puedo desbloquear el mutex para permitir a otros threads ejecutar
        pthread_mutex_unlock(&mutex);
    }
    printf("Soy el thread %d y terminé de ejecutar.\n", tid);
    // Como thread llamo a esta función para terminar mi ejecución
    pthread_exit(NULL);
}

void thread_mutex() {
    // Declaro un arreglo para almacenar todos mis threads
    pthread_t threads[NUM_THREADS_2];
    int thread_args[NUM_THREADS_2];

    // Creo mis threads
    for (int i = 0; i < NUM_THREADS_2; ++i) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function_2, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Ahora como proceso padre tengo que esperar a que mis threads terminen de ejecutar
    // Para eso voy a iterar mi arreglo de threads y llamar la función pthread_join para esperara a los threads
    for (int i = 0; i < NUM_THREADS_2; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Imprimo el valor final del contador
    printf("Valor final del contador: %d\n", counter_2);

    // Destruyo el mutex para que no hayan leaks de memoria
    pthread_mutex_destroy(&mutex);
}

