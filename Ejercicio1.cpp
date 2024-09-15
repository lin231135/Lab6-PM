/*
*------------------------------------------
* pthread_Ejercicio1.cpp
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
* Descripción: Realizar un programa donde se
* se utilicen pthreads para calcular el 
* fibonacci de un número indicado por el 
* usuario, el cual debe de estar entre 0 a 100.
*------------------------------------------
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Se almacenan los parametros para calcular el fibonacci
struct parameters { 
	int valFibonacci; // Valor hasta el cual se calculara el Fibonacci
    int sum; // Variable que almacena la suma de los numeros del fibonacci
};

// Funcion que calculara el valor del fibonacci y su suma
void *calcular(void *arg) {
    struct parameters *param = (struct parameters *)arg;

    // Se extrae el valor hasta el cual se calculara el fibonacci
    int val = param->valFibonacci;
    int x = 0; //Primer numero del fibonacci
    int y = 1; //Segundo numero del fibonacci
    int z = 0; //Variable para continuar el calculo del fibonacci

    param->sum = 0; //Se inicia la suma del fibonacci

    printf("Se realiza el calculo de la serie de fibonacci hasta el numero %d\n", val);

    // Bucle para calcular el fibonacci del valor ingresado
    for(int i =1; i <= val; i++){
        printf("Num: %d: %d\n", i, x);
        param->sum += x;
        z = x + y;
        x = y;
        y = z;
    }
    pthread_exit(NULL); //Se termina el hilo

    return NULL; //Como la funcion es void es necesario regresar un valor de retorno
}

int main()
{
    pthread_t t1; //Se identifica el hilo
    struct parameters param; //Son las variables que almacenaran los valores

    //Bucle que se utiliza para que el valor ingresado este entre 0 a 100
    do{
        printf("Ingrese el valor para calcular el Fibonnacci (debe de estar entre 0 a 100): ");
        scanf("%d", &param.valFibonacci); //Se lee el valor ingresado
    }while (param.valFibonacci < 0 || param.valFibonacci > 100); //Se verifica que el valor ingresado este entre 0 a 100

    pthread_create(&t1, NULL, calcular, &param); //Crea un nuevo hilo y se ejecuta la funcion de calcular

    pthread_join(t1, NULL); //Es para esperar que el hilo que se acaba de crear termine su proceso

    printf("La suma total de los numeros de fibonacci es: %d", param.sum);

    return 0;

}