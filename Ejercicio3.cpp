/*
*------------------------------------------
* Ejercicio3.cpp
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
* Descripcion:Este programa calcula la suma parcial de la serie geométrica alternante utilizando Pthreads. 
*    El usuario ingresa el valor máximo de n (n_max) y se crean hilos para calcular cada término de la serie: 
*    (-1)^(n+1) / n. Cada hilo almacena su resultado, y el hilo principal los suma al finalizar.
*------------------------------------------
*/

#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

// Estructura  que almacena los datos que cada hilo va a procesar: el valor de n y el resultado del cálculo
struct ThreadData {
    int n;
    double result;
};

// Función que calcula el valor de cada término de la serie usando n como entrada
void* calcularTermino(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    // Fórmula que calcula el valor de cada término de la serie geométrica
    data->result = pow(-1, data->n + 1) / (double)data->n;
    pthread_exit(0);
    return NULL; // Este return evita una advertencia del compilador
}

int main() {
    int n_max;
    
    // Pedir al usuario que ingrese el valor máximo de n que vamos a evaluar en la serie
    std::cout << "Ingrese el valor maximo para n: ";
    std::cin >> n_max;

    // Vectores que almacenan los hilos y los datos de cada hilo (uno para cada término de la serie)
    std::vector<pthread_t> hilos(n_max);
    std::vector<ThreadData> datos(n_max);

    // Se crean n hilos, uno para cada término de la serie, y les pasamos sus datos correspondientes
    for (int i = 0; i < n_max; ++i) {
        datos[i].n = i + 1; // Asignamos el valor de n para cada hilo
        pthread_create(&hilos[i], NULL, calcularTermino, (void*)&datos[i]);
    }

    // Usar pthread_join para esperar a que todos los hilos terminen y sumamos sus resultados para almacenarlo en 'suma'
    double suma = 0.0;
    for (int i = 0; i < n_max; ++i) {
        pthread_join(hilos[i], NULL);  // Esperamos que cada hilo termine
        suma += datos[i].result;       // Sumamos el resultado calculado por cada hilo
    }

    // Se muestra el resultado total de la sumatoria de la serie
    std::cout << "Resultado de la serie: " << suma << std::endl;

    return 0;
}