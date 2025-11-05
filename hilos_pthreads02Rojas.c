/**********************************************************
*            Pontificia Universidad Javeriana              * 
*                         ---=---                          *
*                                                          *
* Autores: - Danna Gabriela Rojas Bernal                   *                     * 
* Fecha: 30 Octubre de 2025                                *
* Docente: J. Corredor                                     *
* Objetivo: lab02-> implemntar multiples hilos POSIX       *
*                                                          *
* Descripción:Este programa demuestra la creación y        *
* manejo de múltiples hilos POSIX (pthread) en C. 	   +
* Se generan 10 hilos que se ejecutan de forma concurrente,*
* cada uno imprime su número y su identificador único (ID).* 
* Además, se utiliza un mutex para evitar condiciones de   *
* carrera al incrementar el counter. Al finalizar, se	   *
* muestra el valor total del contador, indicando cuántos   *
* hilos se ejecutaron correctamente. 			   *
***********************************************************/

//librerias
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//se define el numero de hilos a crear 
#define NTHREADS 10
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;//inicializacion del mutex 
int counter = 0;//varible global 

//funicon que ejecutara cada hilo 
void *thread_function(void *arg) {
    int i = *(int *)(arg);// se obtiene el numero de hilo desde el argumento 
    printf("Thread number: %d | Thread ID %lu\n", i, (unsigned long)pthread_self());

//incremento del contador protegido por mutex  
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1); //libera el acceso para otros hilos 

    return NULL;
}

//proceos principal
void main() {
    pthread_t thread_id[NTHREADS];//arreglo de identificadores de hilos 
    int i, j;
    int args[NTHREADS];//arreglo para almacenar los numeros de hilos 

//creacion de hilos 
    for (i = 0; i < NTHREADS; i++) {
        args[i] = i;//Se asigna un numero a cada hilo                 
        pthread_create(&thread_id[i], NULL, thread_function, &args[i]);
    }

    // Esperar a que todos los hilos terminen
    for (j = 0; j < NTHREADS; j++) {
        pthread_join(thread_id[j], NULL);
    }

    printf("Final counter value: %d\n", counter);
}
