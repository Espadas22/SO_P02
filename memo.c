/*
Sistemas operativos, Grupo 05, Semestre 2023-2
    Programa #02 - Simulación de uso de memoria mediante vector de áreas libres

Objetivo:
    Generar una representación visual del método de manejo de memoria de vector
    de áreas libres, utilizado en sistemas linux, donde se represente como la
    disponibilidad de la memoria real afecta la distribución de áreas en el vector 

Integrantes:
    Espadas Rodriguez Anthony Jonathan  - 421033621
    Genaro Vidal Hector                 - 421005011

Fecha de entrega: 
    08-06-2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Definicion de estructuras */


/* Prototipos de funciones */
void imprimirMemoria();                                                                 // Muestra en pantalla el uso de memoria y el vector de areas libres
void ejecutarArchivo();                                                                 // Toma y ejecuta las instrucciones del archivo
void resetarMemorias();                                                                 // Devuelve la memoria y el vetcor de areas libres a su estado inicial

/* Variables globales */
int areasLibres[5] = {0,0,0,0,16};                                                                     // Arreglo que se usara para el vector de areas libres. 
int memoriaReal[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                                                                    // Arreglo que se usara para la simulacion de la memoria real

int main()
{
    imprimirMemoria();
    return (0);
}


/* Definición de las funciones */
void imprimirMemoria()
{
    int i, j = 0;                                                                       // Variables auxiliares de conteo

    system("clear");                                                                    // Limpia la pantalla
    printf("\tMemoria real\n");                                                         // Encabezado de la tabla de memoria real
    printf("Direccion\tProceso\n");                                                     // Separadores de seccion de memoria real
    for(i = 0; i < 16; ++i)                                                             // Recorre la memoria real para imprimir los procesos
    {
        printf("   %d\t\t   %d", i, memoriaReal[i]);                                    // Imprime la dirección de memoria y el proceso ocupandola

        if (i > 8)                                                                      // Comienza a imprimir el vector de areas libres
        {
            if (i == 9)
            {
                printf("\t\t\tVector de areas libres");
            }
            else if  (i == 10)
            {
                printf("\t\tPotencia\tGrupos disponibles");
            }
            else
            {
                printf("\t\t   %d\t\t\t%d", j, areasLibres[j]);
                j++;
            }
        } 
            
        printf("\n");                                                                   // Coloca el salto de renglon
    }
}

void ejecutarArchivo()
{
    /* Defineme prro */
}

void resetarMemorias()
{
    /* Defineme prro */
}

/* ------ Conclusiones 

Espadas:
    

Genaro:
    

*/