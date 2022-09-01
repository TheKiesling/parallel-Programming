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
#include <unistd.h>

using namespace std;

//Subrutina que efectúa el cálculo de n de la serie
void *serie(void *tID){
    float *x;
    x = (float *) tID; //Cast a valor flotante
    
    *x = *x + 1;
    float *result = (float *)malloc(sizeof(float)); //Utilizar memoria heap para asegurar el espacio de memoria
    *result = 1 / (*x * (*x + 1)); //Cálculo n de la serie
    return (void *) result; //Retornar el cálculo
}

int main(){
    long n = 5;
    float sum = 0.0;
    void *result;

    cout << "Ingrese el valor máximo de la serie geométrica: ";
    cin >> n;
    pthread_t thread_id; 
    
    for (int i = 0; i < n; i++){
        float v = (float)i;
        pthread_create(&thread_id, NULL, serie, (void *)&v); //Creación de Hilos
        pthread_join(thread_id, &result); //Esperar a que termine el hilo
		float *resultF = (float *)result; //castear el resultado del hilo a *float
        sum += *resultF;
		free(result); //Liberar memoria
		
    }
    
    printf("Resultado de la serie geométrica es: %f\n", sum);
}