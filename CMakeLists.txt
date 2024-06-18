cmake_minimum_required(VERSION 3.28)
project(Clase5 C)

set(CMAKE_C_STANDARD 11)

add_executable(Clase5 forks.c
        forks_pipes.c
        main.c
        forks.h
        forks_pipes.h
        shared_memory.h
        shared_memory.c
        threads.h
        threads.c
        threads_semaphores.h
        threads_semaphores.c
        thread_mutex.h
        thread_mutex.c
)
