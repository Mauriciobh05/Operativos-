/********************************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mauricio Beltrán Huertas
 * Fecha: 05 noviembre 2025
 * Clase: Sistemas Operativos
 * Descripción: Cálculo de sumatoria paralela con OpenMP y medición de tiempo.
 * Utiliza la función sin() y la cláusula 'reduction' para combinar los resultados de
 * todos los hilos sin generar condiciones de carrera. Se mide el tiempo total de ejecución
 * con gettimeofday().
 ********************************************************************************************/

#include <stdio.h>      // Interfaz de entrada y salida, print 
#include <stdlib.h>     // Interfaz para las funciones generales
#include <math.h>       // Interfaz matemática
#include <omp.h>        // Interfaz para paralelismo OpenMP
#include <sys/time.h>   // Interfaz Para medir el tiempo de ejecución

// Se crean las variables globales para almacenar los tiempos de inicio y fin
struct timeval inicio, fin;

// Se crea la función que inicia la medición de tiempo
void InicioMuestra(){ 
    gettimeofday(&inicio, (void*)0); 
}

// Se crea la función que finaliza la medición y calcula el tiempo total en microsegundos
void FinMuestra(){
    gettimeofday(&fin, (void*)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
    printf("Tiempo total: %.0f µs\n", tiempo);
}

// Se crea la función que calcula una parte de la sumatoria para el índice i
double f(int i) {
    int j, start = i * (i + 1) / 2, finish = start + i;
    double val = 0;

    //Se hace la suma parcial de valores seno desde 'start' hasta 'finish'
    for (j = start; j < finish; j++)
        val += sin(j);

    return val; // Retorna el resultado acumulado para esa sección
}

int main(int argc, char *argv[]) {
    // Se verificación los argumento osea los numeros de hilos 
    if (argc != 2) {
        printf("Uso: ./lab05 numHilos\n");
        return -1;
    }

    // Se convierte el argumento a entero y configuración de OpenMP
    int numHilos = atoi(argv[1]);
    omp_set_num_threads(numHilos);

    double sum = 0.0; // Se crea el acumulador global con reducción
    int n = 30000;    // Se crea el límite de la sumatoria

    printf("OpenMP ejecutando con %d hilos\n", numHilos);

    // Se inicia la medición del tiempo
    InicioMuestra();

    // Región paralela con reducción y planificación dinámica
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (int i = 0; i <= n; i++)
        sum += f(i);

    // Finaliza la medición del tiempo y muestra el resultado
    FinMuestra();

    // Se muestra la sumatoria total combinada por OpenMP
    printf("La sumatoria es: %.2f\n", sum);

    return 0; // Fin del programa
}
