/**********************************************************
*            Pontificia Universidad Javeriana              *
*                         ---=---                          *
*                                                          *
* Autores: - Danna Gabriela Rojas Bernal                   *
* Fecha: 30 Octubre de 2025                                *
* Docente: J. Corredor                                     *
* Objetivo: Aplicar el uso de hilos POSIX y mutex          *
*                                                          *
* Descripción:                                             *
* Suponer que x*x es un cálculo altamente costoso          *
* computacionalmente. Se desea calcular la suma de los     *
* cuadrados usando HILOS POSIX. Se debe aplicar paralelismo*
* para que cada hilo calcule un cuadrado.                  *
*                                                          *
*  Analisis: Se arregla el código para evitar la condición * 
* de carrera (Race Condition) utilizando un mutex 	   *
* que protege el acceso a la variable global 'acumulado'.  *
***********************************************************/
//librerias 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
//variable  Globales
int acumulado=0;
//CC: condicion de carrera
pthread_mutex_t bloqueoCC= PTHREAD_MUTEX_INITIALIZER;

void *cuadrados (void *x){
//se casta al tipo entero el puntero de argumento
int xi=(intptr_t)x;


    // Se bloquea el acceso a la variable global antes de modificarla
  pthread_mutex_lock(&bloqueoCC);
  acumulado +=xi*xi;
  pthread_mutex_unlock(&bloqueoCC);// se libera el bloqueo 

return NULL;
}

//PROCESO INCIIAL 
int main(){

//declaracion y creacion de 20 hilos 

pthread_t workersTh[20];
for(int i=0;i<20;i++){
pthread_create (&workersTh[i],NULL, &cuadrados,(void*)(intptr_t)(i+1));
}
//esperar a cada hilo termine 
for(int i=0;i<20;i++){
void *acumulado;
pthread_join( workersTh[i], &acumulado);
}

//se presenta el valor resultado 
printf("Valor suma cuadrados= %d \n",acumulado);
return 0;
}
