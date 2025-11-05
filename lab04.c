/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Ejemplo del uso de variables privadas en OpenMP.
 * En esta versión, las variables i, a y b son privadas.
 * Se muestra cómo el uso de private(b) evita que la variable b se comparta entre hilos,
 * haciendo que el valor global de b no se modifique.
 ********************************************************************************************/

#include <omp.h>      // interfaz  para paralelismo con OpenMP
#include <stdio.h>   // Interfaz estándar para entrada y salida print
#include <stdlib.h>  // Interfaz para funciones generales  
  
int main(){
    int i;              // Se crea la variable de control del ciclo

    const int N = 1000; // Se crea el límite del bucle for
    int a = 50;         // Se crea la variable base

    int b = 0;          // Variable que se volverá privada en la región paralela

    // Región paralela con distribución del bucle.
    // Cada hilo tendrá su propia copia de i, a y b, por esa razon b no se compartirá.
    #pragma omp parallel for private(i) private(a) private(b) // Todas las variables son locales por hilo
    for (i = 0; i < N; i++){
        b = a + i; // Cada hilo trabaja con su propia versión de b
    }

    // Al final, el valor global de b no cambia porque cada hilo tenía su copia privada.
    printf("a = %d b = %d (Se espera a = 50 b = 1049)\n", a, b);

    return 0; // Fin del programa
}
