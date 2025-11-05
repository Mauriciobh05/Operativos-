/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Cálculo de sumatoria paralela con OpenMP y la función seno (sin()).
 * Se utiliza la cláusula 'reduction' para combinar los resultados de los hilos sin 
 * generar condiciones de carrera. Cada hilo ejecuta una parte de la sumatoria.
 ********************************************************************************************/

#include <stdio.h>     // Interfaz de entrada y salida print
#include <stdlib.h>    // Interfaz Funciones de utilidad 
#include <time.h>      // Interfaz de tiempo 
#include <omp.h>       // Interfaz para paralelismo OpenMP
#include <math.h>      // Interfaz de Funciones matemáticas 

#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // Se  obtiene el mínimo entre dos valores

// Función que calcula una porción de la sumatoria para el índice i
double f(int i) {
    int j, start = i * (i + 1) / 2, finish = start + i;
    double return_val = 0;

    // Bucle interno que acumula la suma de los valores seno
    for (j = start; j < finish; j++)
        return_val += sin(j);

    return return_val; // Devuelve la suma parcial para ese i
}

int main(int argc, char *argv[]) {

    // Se validan los argumentos,  se espera solo un argumento (número de hilos)
    if (argc != 2) {
        printf("Error\n\tUso correcto: ./ejecutable numHilos\n");
        return -1;
    }

    // Conversión del argumento a entero y configuración de hilos
    int numHilos = atoi(argv[1]);
    omp_set_num_threads(numHilos); // Se fija el número de hilos activos

    double sum = 0.0;  // Se crea la variable global donde se acumula la suma total
    int i, n = 30000;  // Se ctrea el límite superior de la sumatoria

    printf("OpenMP ejecutando con %d hilos\n", numHilos);

    // Región paralela
    #pragma omp parallel
    {
        int threads = omp_get_num_threads(); // Se obtiene cuántos hilos se crearon realmente

        // Solo el hilo maestro imprime esta información
        #pragma omp master
        printf("Número de hilos detectados: %d\n", threads);

        // Se distribuye el bucle entre hilos y aplica reducción sobre 'sum'
        #pragma omp for reduction(+:sum)
        for (i = 0; i <= n; i++) {
            sum += f(i); // Cada hilo ejecuta parte de la sumatoria
        }
    }

    // Se muestra el resultado total combinado por OpenMP
    printf("La sumatoria es: %.2f\n", sum);

    return 0; // Fin del programa
}
