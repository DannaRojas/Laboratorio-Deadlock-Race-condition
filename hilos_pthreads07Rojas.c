/**********************************************************
*            Pontificia Universidad Javeriana             *
*                         ---=---                         *
*                                                         *
* Autores: - Danna Gabriela Rojas Bernal                  *
* Fecha: 30 Octubre de 2025                               *
* Docente: J. Corredor                                    *
* Objetivo:Lab07-> Aplicar el uso de hilos POSIX y mutex  *
*                                                         *
* Descripción:   se tiene 2 funciones para asignar y	  *
* reportar en funcion de la llamada desde los hilos	  *
* creados, desde el proceso principal (main)              *
*                                     			  *
*******************Analisis de resultado******************* 
* Aunque el programa compila correctamente, 		  *
* no funciona del todo bien porque las secciones que usan * 
* mutex y variables de condición están comentadas. Esto	  * 
* hace que los hilos no se sincronicen, y el hilo que 	  *
* imprime el valor puede hacerlo antes de que se actualice.* 
* Al no existir control sobre el acceso concurrente, 	   *
* se genera una posible condición de carrera (race condition)		
*					                   *
***********************************************************/


//librerias
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

//variables globales
int valor = 100;
bool notificar = false;

// Declaración e inicialización de la variable de condición y el mutex
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


// Función que reporta el valor actual
void *reportar(void* nousados){
    
    /*
    pthread_mutex_lock(&mutex);
    while (!notificar)
    {
        pthread_cond_wait(&var_cond, &mutex);
    }
    */
   
    printf("El valor es: %d\n", valor);
    /*
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}



void *asignar(void* nousados){ // Función que asigna un nuevo valor
    
    valor = 20;
    /*
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}

//proceso principal
int main(int argc, char *argv[]){
    pthread_t reporte, asigne;
    
//creacion de hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);
    //espera a que los hilos terminen 
    void * nousado;
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

   
    return 0;
}
