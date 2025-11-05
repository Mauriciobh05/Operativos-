/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Programa básico de introducción a OpenMP. 
 * Crea múltiples hilos de ejecución (20) y cada uno imprime un mensaje “Hello World” 
 * junto con su número de hilo. Demuestra la paralelización básica usando OpenMP.
 ********************************************************************************************/

#include <omp.h>     
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Se define el número de hilos que OpenMP utilizará (20 en este caso)
    omp_set_num_threads(20);

    // Imprime cuántos hilos en total fueron creados
    printf("OpenMP ejecutando con %d hilos\n", omp_get_max_threads());

    // Región paralela: el bloque dentro de 'parallel' se ejecuta en todos los hilos creados
    #pragma omp parallel
    {
        // Cada hilo imprime su número identificador
        printf("Hello World desde el thread %d\n", omp_get_thread_num());
    }

    return 0;
}
