/**********************************************************
*            Pontificia Universidad Javeriana              *
*                         ---=---                          *
*                                                          *
* Autores: - Danna Gabriela Rojas Bernal                   *           >
* Fecha: 30 Octubre de 2025                                *
* Docente: J. Corredor                                     *
* Objetivo: lab08			                   *
*                                                          *
* Descripción: se tiene 2 funciones para asignar y         *
* reportar en funcion de la llamada desde los hilos        *
* creados, desde el proceso principal (main)		   *
*							   *
*                  Analisis de resultado		   *
*							   *
* se corrige la CC al descomentar, de esta manera          *
* se arregla el código para evitar la condición de carrera *
* (Race Condition) utilizando un mutex que protege el      *
* acceso a la variable global				   *
***********************************************************/

//librerias 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Variables globales
int valor = 100;
bool notificar = false;

// Bloqueo y variable de condición para sincronización
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condiCC = PTHREAD_COND_INITIALIZER;

// Función REPORTAR
void *reportar(void *nousada) {

    pthread_mutex_lock(&bloqueoCC);  // Bloquear antes de esperar

    // Espera a ser notificado por el hilo que asigna el valor
    while (!notificar){
        pthread_cond_wait(&condiCC, &bloqueoCC);
    }
    printf("\n\tEl valor es: %d\n", valor);

    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}

// Función ASIGNAR
void *asignar(void *nousada) {
    pthread_mutex_lock(&bloqueoCC);  // Proteger acceso compartido

    valor = 20;          // Se modifica el valor
    notificar = true;    // Se cambia el estado de la bandera

    pthread_cond_signal(&condiCC);  // Despertar al hilo reportar

    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}

// Proceso principal
int main() {
    //Declaracion y creacion 
    pthread_t reporte, asigne;
    pthread_create(&reporte, NULL, &reportar, NULL);
    pthread_create(&asigne, NULL, &asignar, NULL);

    //creo variable para recojer valor al esperar
    void *nousada;
    pthread_join(reporte, &nousada);
    pthread_join(asigne, &nousada);

    // Liberar recursos
    pthread_mutex_destroy(&bloqueoCC);
    pthread_cond_destroy(&condiCC);

    return 0;
}
