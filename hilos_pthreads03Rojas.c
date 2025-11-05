/**********************************************************
*            Pontificia Universidad Javeriana              *
*                         ---=---                          *
*                                                          *
* Autores: - Danna Gabriela Rojas Bernal                   *
* Fecha: 30 Octubre de 2025                                *
* Docente: J. Corredor                                     *
* Objetivo: Lab 03 - Uso de variables de condición y mutex *
*                                                          *
* Descripción: Este programa utiliza dos hilos que         *
* incrementan un contador global de forma sincronizada.    *
* Se emplean mutex y variables de condición para controlar *
* el acceso y coordinar cuándo cada hilo puede ejecutar.   *
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Inicialización de mutex y variable de condición->varibles globales
pthread_mutex_t contador_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_Cond = PTHREAD_COND_INITIALIZER;

// Variable global compartida
int counter = 0;

// Límites del contador
#define FIN_CONTADOR 15
#define ALTO_CONTADOR_01 4
#define ALTO_CONTADOR_02 11

// Función para el primer hilo
void* contador01() {
    for(;;) {
        // Espera cuando el contador esté dentro del rango bloqueado
        pthread_mutex_lock(&condition_Mutex);
        while(counter >= ALTO_CONTADOR_01 && counter <= ALTO_CONTADOR_02) {
            pthread_cond_wait(&condition_Cond, &condition_Mutex);
        }
        pthread_mutex_unlock(&condition_Mutex);

        // Incremento protegido por mutex
        pthread_mutex_lock(&contador_Mutex);
        counter++;
        printf("Valor de contador en funcion ===> 01 <===: %d\n", counter);
        pthread_mutex_unlock(&contador_Mutex);

        // Termina si llega al límite
        if (counter >= FIN_CONTADOR) {
            return NULL;
        }
    }
}

// Función para el segundo hilo
void* contador02() {
    for(;;) {
        // Señala al hilo 01 cuando el contador esté fuera del rango
        pthread_mutex_lock(&condition_Mutex);
        if(counter < ALTO_CONTADOR_01 || counter > ALTO_CONTADOR_02) {
            pthread_cond_signal(&condition_Cond);
        }
        pthread_mutex_unlock(&condition_Mutex);

        // Incremento protegido
        pthread_mutex_lock(&contador_Mutex);
        counter++;
        printf("Valor de contador en funcion ===> 02 <===: %d\n", counter);
        pthread_mutex_unlock(&contador_Mutex);

        // Termina si llega al límite
        if (counter >= FIN_CONTADOR) {
            return NULL;
        }
    }
}

// Proceso principal
int main() {
    pthread_t hilo01, hilo02;

    // Creación de hilos
    pthread_create(&hilo01, NULL, contador01, NULL);
    pthread_create(&hilo02, NULL, contador02, NULL);

    // Espera a que terminen
    pthread_join(hilo01, NULL);
    pthread_join(hilo02, NULL);

    exit(0);
}

/**********************************************************************************
*                              Analisis de resultado                              *
*                                                                                 *
* Al ejecutar el programa, los dos hilos se coordinan para incrementar el contador*
* sin interferirse entre sí. El hilo 01 se detiene cuando el contador está entre  *
* 4 y 11, mientras el hilo 02 continúa y notifica cuando el valor sale de ese     *
* rango.                                                                          *
*                                                                                 *
**********************************************************************************/
