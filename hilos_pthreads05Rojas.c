/********************************************************************
*            Pontificia Universidad Javeriana                       *
*                         ---=---                                   *
*                                                                   *
* Autores: - Danna Gabriela Rojas Bernal                            *
* Fecha: 30 Octubre de 2025                                         *
* Docente: J. Corredor                                              *
* Objetivo: lab05->Calcular la suma de los cuadrados de 1 a 20      *
* usando hilos POSIX						    *                                                                   
* Descripción:							    *
* suponer que x*x es un calculo altamente costoso computacionalmnete*
* Se desea calcular la suma de  cuadrados usando HILOS POSIX. 	    *
* Se debe aplicar paraelislo de cada cuadrado usando los hilo	    *
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

//variable  global 
int acumulado=0;

void *cuadrados (void *x){
//se casta al tipo entero el puntero de argumento
int xi=(intptr_t)x;
acumulado +=xi*xi;
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
// explicar porque no funicona 
/************************************************************************************
*                         Análisis de resultado                                     *  
*									            *
* El programa crea 20 hilos que calculan los cuadrados de 1 a 20 y los 		    *
* suman en una variable compartida. Sin embargo, al no usar sincronización, 	    *
* los hilos acceden a acumulado al mismo tiempo, generando 			    *
* resultados inconsistentes.Esto ocurre por una condición de carrera(RACE CONDITION)*
* que hace que el valor final cambieen cada ejecución.                              *
*************************************************************************************/
