/*
*------------------------------------------
* pthread_Ejercicio2 - Inciso B.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* CC3086 - Programacion de Microprocesadores
*
*------------------------------------------
* Autor 1: Dulce Ambrosio - 231143
* Autor 2: Javier Linares - 231135
*------------------------------------------
* Descripción: Se modifico el ejemplo 
*"HelloWorld" para realizar un ciclo for, 
* para crear hilos y un ciclo for por separado
* para hacer su respectivo join y se imprimira 
* “Hello world thread No. X” colocando el 
* número del hilo en lugar de la “X”.
*------------------------------------------
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10 //cantidad de hilos que se crean

void *PrintHello(void *paramID) {
	int *id;						// puntero a entero
	id = (int *)paramID;			// cast de conversión de tipo void * a int *
	
	
	printf("Hello world thread No. %d\n", *id); //se imprime el mensaje indicado
	pthread_exit(NULL); //se finaliza el hilo
	return NULL; 
}

int main(int argc, char *argv[]) {

	// Usar intptr_t para identificar hilos de manera segura
	pthread_t threadsID[NUM_THREADS];
	
	// Parametro a compartir equivalente al num del n hilo
	int rc, t, param[NUM_THREADS];
	
	// Cada hilo se crea individualmente
	for (t=0; t< NUM_THREADS; t++) {
		param[t] = t;

		rc = pthread_create(&threadsID[t], NULL, PrintHello, (void *)&param[t]);

		// Si algún hilo no pudo crearse, muestra mensaje de error
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	//ciclo para hacer el join de cada hilo
    for (t=0; t < NUM_THREADS; t++){
        pthread_join(threadsID[t], NULL);
    }
	pthread_exit(NULL);	//finaliza el programa 
}