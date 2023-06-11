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
    13-06-2023


-------------------------    **NOTA IMPORTANTE**    ---------------------------------
Debido al uso de la biblioteca math.h debe ser compilado con el comando:
    
                                "gcc memo -lm"

-------------------------------------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* Definicion de estructuras */
typedef struct _nodo NODO;
typedef struct _lista LISTA;

struct _nodo{                                                                           // Estructura que guarda los grupos de areas libres
    int inicio;                                                                         // Indica el inicio del area libre
    int fin;                                                                            // Indica el fin del area libre
    NODO* siguiente;                                                                    // De existir, apunta a la siguiente area libre
};

struct _lista{                                                                          // Estructura para agrupar las areas libres de un mismo tamaño
    int tam;                                                                            // Indica el tamaño de las areas libres de la lista
    NODO* inicio;                                                                       // Indica el primer nodo de la lista
};


/* Prototipos de funciones */
void imprimirMemoria();                                                                 // Muestra en pantalla el uso de memoria y el vector de areas libres
void ejecutarArchivo();                                                                 // Toma y ejecuta las instrucciones del archivo
void resetarMemorias();                                                                 // Devuelve la memoria y el vetcor de areas libres a su estado inicial

LISTA* crearLista();                                                                    // Reserva la memoria para una nueva lista
int es_vacia(LISTA* lista);                                                             // Determina si una lista es vacia
void vaciarAreasLibres ();                                                              // Libera el espacio reservado para las listas
void generarListas();                                                                   // Genera las listas vacias para el vector de areas libres
void imprimirLista(LISTA* lista);                                                       // Imprime todos los nodos (areas libres) de una lista


/* Variables globales */
LISTA* areasLibres[5];                                                                  // Arreglo que se usara para el vector de areas libres. 
int memoriaReal[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                                                                    // Arreglo que se usara para la simulacion de la memoria real


/* Metodo main */
int main()
{
    generarListas();
    imprimirMemoria();
    vaciarAreasLibres();
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
                imprimirLista(areasLibres[j]);
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

LISTA* crearLista(int tam)
{
    LISTA* nueva_lista = (LISTA*) malloc(sizeof(LISTA));
    nueva_lista -> inicio = NULL;
    nueva_lista -> tam = tam; 
    return nueva_lista;
}

void generarListas()
{
    for (int i = 0; i < 5; ++i)
    {
        areasLibres[i] = crearLista(pow(2,i));                                          // Crea la lista segun la potencia correspondiente
    }    
}

void imprimirLista(LISTA* lista)
{
    //printf("\t\t   %d\t\t\t%d", j, areasLibres[j]);
    printf("\t\t   %d\t\t\t", lista -> tam);                                            // Imprime el tamaño de las areas de la lista

    if (es_vacia(lista))                                                                // Para listas vacias...
    {
        printf("--");                                                                   // ... no se imprime informacion
    }
    else
    {
        // Colocacion de corrimiento de nodos
    }
}

void vaciarAreasLibres ()
{
    for (int i = 0; i < 5; ++i)
    {
        //vaciarLista(areasLibres[i]);                                                    // Vacia todos los nodos
        free(areasLibres[i]);                                                           // Libera el espacio de la lista
    }
}

int es_vacia(LISTA* lista){
    if(lista->inicio == NULL) return 1;
    return 0;
}

/* ------ Conclusiones 

Espadas:
    

Genaro:
    

*/