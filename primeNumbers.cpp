/*
#      #    #######    ########   #######   #          #######   ##      #    #########
#     #        #       #          #         #             #      # #     #    #
#    #         #       #          #         #             #      #  #    #    #
####           #       #####      #######   #             #      #   #   #    #    ####
#    #         #       #                #   #             #      #    #  #    #       #
#     #        #       #                #   #             #      #     # #    #       #
#      #    ########   ########   #######   ########   #######   #      ##    #########
*/

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>

using namespace std;

//Estructura que posee los parámetros necesarios para ejecutar la subrutina
typedef struct{
    int nThreads;   //Número de Hilos (Ingresado)
    int maxValue;   //Valor máximo (Ingresado)
    int n;          //Número de números a analizar por Hilo
    int id;         //ID del Hilo
    int sum;        //Suma de los números del Hilo
}values;

//Función que determina si el número es primo
int prime(int number){
    if (number > 1){
        for(int i = 2; i <= number/2 ; i++)
            if (number % i == 0)
                return 0;
        return 1;
    }
    else{
        return 0;
    }
}

//Subrutina a ejecutar por el Hilo
void *funcion_thr (void *ioValues){
    //Cast del parametro a la estructura creada
    values *ioValuesC = ((values*) (ioValues));     
    
    //Obtener cada valor de la estructura
    int tid = ioValuesC->id;
    int n = ioValuesC->n;
    int nThreads = ioValuesC->nThreads;
    int maxValue = ioValuesC->maxValue;
    
    //Declaración de variables que se imprimiran por hilo
    int sum = 0;
    int limInf = tid * n;
    int limSup = (tid + 1) == nThreads ? (maxValue + 1) : ((tid + 1) * n);
    
    printf("THREAD %d\nLim inf: %d\nLim sup (no incluido): %d\n", tid, limInf, limSup);
    
    //Análisis de los números asignados al Hilo
    for(int i = limInf; i < limSup ; i++)
        if(prime(i)){
            printf("%d\n", i);
            sum += i;
        }
    
    //Asignar la suma de los números primos a la estructura y devolver el valor
    ioValuesC->sum = sum;
    pthread_exit(&(ioValuesC->sum));
}

int main(){
    int nThreads, maxValue, n, res, *sum, totalSum = 0;

    //Solicitud de datos
    cout << "Ingrese el valor máximo: ";
    cin >> maxValue;
    cout << "Ingrese el número de threads para realizar el cálculo: ";
    cin >> nThreads;

    pthread_t tabla_thr[nThreads]; //Arreglo con los TID
    values param[nThreads]; //Arreglo de parámetros
    
    //Cálculo e impresión de las operaciones a efectuar
    n = maxValue / nThreads;
    res = maxValue % nThreads;
    cout << "\nCantidad de valores a evaluar por thread: " << n << " y residuo: " << res << endl;
    cout << "Buscando primos entre 0 y " << maxValue << endl;

    //Ciclo de creación y finalización de los Hilos
    for (int i=0; i < nThreads; i++) { 
        //Asignar los parámetros a la estructura de cada Hilo
        param[i].maxValue = maxValue;
        param[i].nThreads = nThreads;
        param[i].n = n;
        param[i].id = i;
        
        cout << "---------------------------------------------\n";
        
        //Creación de Hilos
		pthread_create(&tabla_thr[i], NULL, &funcion_thr, (void *)&param[i]);
		
		//Terminan los Hilos y se obtiene el valor de la suma de los mismos
		pthread_join(tabla_thr[i], (void **)&sum);
		printf("Suma hilo: %d\n",*sum);
		totalSum += *sum;
	}
	//Impresión de la suma total
	printf("Suma TOTAL: %d\n", totalSum);
	
	//Se destruyen los Hilos y se termina el programa
	pthread_exit(NULL);
	return 0;
}