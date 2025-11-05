/**********************************************************
*            Pontificia Universidad Javeriana              *
*                         ---=---                          *
*                                                          *
* Autores: - Danna Gabriela Rojas Bernal                   *
* Fecha: 30 Octubre de 2025                                *
* Docente: J. Corredor                                     *
* Objetivo: Lab 04 - Implementar el uso de hilos y mutex   *
*                                                          *
* Descripción: Este programa crea tres hilos que simulan   *
* cargas de trabajo. Cada hilo incrementa un contador      *
* global protegido por un mutex para evitar condiciones    *
* de carrera. Se muestra el inicio y finalización de cada  *
* carga de manera sincronizada.                            *
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Declaración de variables locales 
int counter = 0;
pthread_t IDhilo[3];// Arreglo para almacenar los identificadores de los tres hilos
pthread_mutex_t bloqueo = PTHREAD_MUTEX_INITIALIZER;// Mutex para evitar acceso concurrente al contador

//función para cada hilo
void *cargarHilo() {
    unsigned long i = 0;
 // Bloqueo del mutex para que solo un hilo modifique el contador a la vez
    pthread_mutex_lock(&bloqueo);
    counter += 1;
    printf("\n\t=> Carga %d ha inicializado <=\n", counter);
//inico de blucle 
    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("\n\t=> Carga %d ha finalizado <=\n", counter);
// Desbloquea el mutex para permitir que otro hilo entre    
pthread_mutex_unlock(&bloqueo);
    return NULL;
} 

//proceso principal
int main() {
    int error, i = 0;

    //creación de los hilos
    while (i < 3) {
        error = pthread_create(&(IDhilo[i]), NULL, &cargarHilo, NULL);
        if (error != 0) {
            printf("\nHILO NO CREADO [%d]\n", error);
        }
        i++;
    }

    //esperar a que cada hilo termine
    i = 0;
    while (i < 3) {
        pthread_join(IDhilo[i], NULL);
        i++;
    }

    return 0;
}
/**********************************************************************************
*                              Analisis de resultado                              *
*                                                                                 *
* Al ejecutar el programa se nota que los tres hilos trabajan de forma            *
* ordenada gracias al mutex, que impide que varios accedan                        *
* al contador al mismo tiempo.Cada hilo muestra cuándo inicia y termina su carga, *
* simulando una tarea pesada dentro de un ciclo. Aunque los hilos se              *
* ejecutan de manera concurrente, el bloqueo hace que                             *
* los mensajes aparezcan uno tras otro, sin mezclarse.                            *
*                                                                                 *
**********************************************************************************/
