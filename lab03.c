/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Ejemplo del uso de variables privadas en OpenMP.
 * Este programa muestra cómo el uso de la cláusula 'private' afecta el valor
 * de las variables dentro de una región paralela.
 ********************************************************************************************/

#include <omp.h>      // Interfaz para paralelismo con OpenMP
#include <stdio.h>    // Interfaz estándar para entrada y salida print
#include <stdlib.h>   // Interfaz para funciones generales 

int main(){
    int i;              // Se crea la variable de control del ciclo
    const int N = 1000; // Se crea el límite del bucle for
    int a = 50;         // Se crea la variable base
    int b = 0;          // Se crea la variable compartida pero no es privada

    // Se crea una región paralela con un bucle for distribuido entre varios hilos.
    // Las variables 'i' y 'a' son privadas 
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++){
        // b es compartida, por esa razon  todos los hilos escriben sobre la b .
        // Esto hace que se genera una condición de carrera: el valor final depende del último hilo en ejecutar.
        b = a + i;
    }

   // b mostrará el último valor escrito por algún hilo condición de carrera
    printf("a = %d b = %d (Se espera a = 50 b = 1049)\n", a, b);

    return 0; // Fin del programa
}
