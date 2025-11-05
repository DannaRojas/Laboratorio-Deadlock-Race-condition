/*************************************************************
*            Pontificia Universidad Javeriana                *
*                         ---=---                            *
*                                                            *
* Autores: - Danna Gabriela Rojas Bernal                     *
* Fecha: 30 Octubre de 2025                                  *
* Docente: J. Corredor                                       *
* Objetivo:Lab01->Comprender el uso básico de hilos POSIX    *
* (pthread) en C mediante la creación y ejecución concurrente*
* de dos hilos que imprimen mensajes diferentes.             *
*               					     *
* Descripción: Este programa demuestra el uso básico de	     *
* hilos POSIX (pthread) en C. Se crean dos hilos 	     *
* independientes que ejecutan una misma función encargada    *
* de imprimir un mensaje distinto. Cada hilo se ejecuta      *
* de manera concurrente, mostrando cómo varias tareas pueden *
* correr al mismo tiempo dentro de un mismo programa.        *                                           *
**************************************************************/

//declaracion librerias 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Función que ejecutará cada hilo, imprime un mensaje recibido como argumento
void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;//puntero 
    printf("%s \n", message);//imprimi mensaje correspondiente al hilo 
    return NULL;
}

//funcion principal 
int main() {
    pthread_t thread1, thread2;//identificador de los dos hilos
    char *message1 = "Thread 1";//mensaje primer hilo 
    char *message2 = "Thread 2";//mensjae segundo hilo
    int  iret1, iret2;

// Creación de los dos hilos que ejecutan la misma función con diferentes mensajes
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

// Muestra los códigos de retorno de la creación de cada hilo
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

// Espera a que ambos hilos terminen su ejecución antes de finalizar el programa    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
