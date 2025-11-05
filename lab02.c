/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Programa que demuestra cómo establecer y controlar el número de hilos
 * de ejecución en OpenMP. El número de hilos se pasa como argumento al programa.
 * Cada hilo imprime su identificador junto con el total de hilos creados.
 ********************************************************************************************/

#include <stdio.h>    // Interfaz estándar para entrada y salida 
#include <stdlib.h>   // Interfaz para funciones de conversión 
#include <time.h>     // Interfaz para manejo de tiempo 
#include <omp.h>      // Interfaz que permite usar OpenMP para paralelismo

int main(int argc, char *argv[]) {

    /* Fijar número de hilos */
    if (argc != 2) {
        printf("Error\n\tUso correcto: ./ejecutable numHilos\n");
        return -1; // Termina el programa con código de error
    }

    // Convierte el argumento recibido en texto  a número entero
    int numHilos = atoi(argv[1]);

    // Se fija el número de hilos que OpenMP usará para la ejecución paralela
    omp_set_num_threads(numHilos);

    // Se obtiene el número máximo de hilos configurado 
    int maxHilos = omp_get_max_threads();

    // Se imprime mensaje indicando la cantidad de hilos que OpenMP utilizará
    printf("OpenMP ejecutando en Cores (HiperThreading) con %d hilos\n", maxHilos);

    // Bloque de código que se ejecutará en paralelo
    #pragma omp parallel
    {
        //Se obtiene el identificador único del hilo actual 
        int id = omp_get_thread_num();

        // Cada hilo imprime su número junto con el total de hilos creados
        printf("Hola desde el hilo %d de %d\n", id, numHilos);
    }

    return 0;
}
