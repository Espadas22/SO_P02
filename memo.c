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
int esVacia(LISTA* lista);                                                              // Determina si una lista es vacia
void vaciarAreasLibres ();                                                              // Libera el espacio de las listas del vector
void vaciarLista(LISTA* lista);                                                         // Elimina todos los nodos de una lista
void generarListas();                                                                   // Genera las listas vacias para el vector de areas libres
void imprimirLista(LISTA* lista);                                                       // Imprime todos los nodos (areas libres) de una lista

NODO* crearNodo(int inicio, int fin, NODO* siguiente);                                  // Genera un nuevo nodo
void enlistar(LISTA* lista, NODO* nodo);                                                // Agrega un nodo a una lista


/* Variables globales */
LISTA* areasLibres[5];                                                                  // Arreglo que se usara para el vector de areas libres. 
int memoriaReal[16];                                                                    // Arreglo que se usara para la simulacion de la memoria real


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
        printf("   %d\t\t  ", i);                                                       // Imprime la dirección de memoria y el proceso ocupandola

        if (memoriaReal[i] != 0)
            printf("%3d", memoriaReal[i]);
        else
            printf("---");

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
};

void resetarMemorias()
{
    /* Defineme prro */
};

LISTA* crearLista(int tam)
{
    LISTA* nueva_lista = (LISTA*) malloc(sizeof(LISTA));
    nueva_lista -> inicio = NULL;
    nueva_lista -> tam = tam; 
    return nueva_lista;
};

void generarListas()
{
    for (int i = 0; i < 16; ++i)                                                        // Llena el vector de areas libres y la memoria real
    {
        if (i < 5)
            areasLibres[i] = crearLista(pow(2,i));                                      // Crea la lista segun la potencia correspondiente
        
        memoriaReal[i] = 0;                                                             // Coloca los valores de inicio en la memoria real
    }

    NODO* primer_bloque = (NODO*) malloc(sizeof(NODO));                                 // Generamos el primer bloque de la lista
    primer_bloque = crearNodo(0, 15, NULL);                                             // Le asignamos espacio
    enlistar(areasLibres[4], primer_bloque);                                            // Lo enviamos a la lista correspondiente    
};

void imprimirLista(LISTA* lista)
{
    printf("\t\t   %d\t\t\t", lista -> tam);                                            // Imprime el tamaño de las areas de la lista

    if (esVacia(lista))                                                                 // Para listas vacias...
    {
        printf("--");                                                                   // ... no se imprime informacion
    }
    else
    {
        NODO* corredor = (NODO*) malloc(sizeof(NODO));                                  // Nodo que nos ayudara a recorrer la lista
        corredor = lista -> inicio;                                                     // Comenzamos al inicio de la lista
        
        printf("%2d", corredor -> inicio);                                              // El primer numero siempre se imprime
        corredor = corredor -> siguiente;                                               // Avanzamos al siguiente elemento
        
        while (corredor != NULL)                                                        // Se continua mientras corredor apunte a un nodo
        {
            printf(" %c %d", '<', corredor -> inicio);                                  // Imprime la siguiente area
            corredor = corredor -> siguiente;                                           // Avanzamos al siguiente nodo
        };

        free(corredor);                                                                 // Enviamos a corredor de viaje a Belice
    };
};

void vaciarAreasLibres ()
{
    for (int i = 0; i < 5; ++i)
    {
        vaciarLista(areasLibres[i]);                                                    // Vacia todos los nodos
        free(areasLibres[i]);                                                           // Libera el espacio de la lista
        areasLibres[i] = NULL;                                                          // Se pierde la refrencia
    }
};

int esVacia(LISTA* lista){
    if(lista->inicio == NULL) return 1;                                                 // Notifica si la lista apunta a algun nodo
    return 0;
};

void vaciarLista(LISTA* lista)                                                          // Se recibe la lista  a vaciar
{
    NODO* kamikaze = lista -> inicio;                                                   // Nodo que sacrificara su vida por el proyecto
    
    while (kamikaze != NULL)                                                            // Continuara mientras haya nodos en la lista
    {
        lista -> inicio = kamikaze -> siguiente;                                        // Se desplaza el inicio de la lista
        kamikaze -> siguiente = NULL;                                                   // Se pierde la referencia a la lista
        free(kamikaze);                                                                 // Se libera el espacio reservado
        kamikaze = lista -> inicio;                                                     // Regresamos al inicio de la lista        
    };

    free(kamikaze);                                                                     // Despedimos con honores a un nodo muy valiente
    lista -> tam = 0;                                                                   // Eliminanmos el tamaño de la lista
};

NODO* crearNodo(int inicio, int fin, NODO* siguiente)                                   // Se reciben los parámetros
{
    NODO* nuevo_nodo  = (NODO*) malloc(sizeof(NODO));                                   // Se reserva la memoria
    nuevo_nodo -> inicio = inicio;                                                      // Se asignan los valores correspondientes
    nuevo_nodo -> fin = fin;
    nuevo_nodo -> siguiente = siguiente;
    return nuevo_nodo;                                                                  // Se devuelve la direccion de nodo
};

void enlistar(LISTA* lista, NODO* nodo)                                                 // Recibe la lista y el nodo a agregar
{
    if (esVacia(lista))                                                                 // Para listas vacias sólo se agrega                                  
    {
        lista -> inicio = nodo;                                                         // Se coloca directo al inicio
        nodo -> siguiente = NULL;                                                       // Se pierde su anterior referencia
    }
    else if (nodo -> inicio < lista -> inicio -> inicio)                                // Si el nuevo nodo es menor que el inicio
    {
        nodo -> siguiente = lista -> inicio;                                            // El nodo apunta al inicio
        lista -> inicio = nodo;                                                         // Desplazamos el inicio al nuevo nodo
    }
    else if (lista -> inicio -> siguiente == NULL)                                      // Cuando no es menor pero solo hay un nodo
    {
        lista -> inicio -> siguiente = nodo;                                            // Se coloca al final de la lista
        nodo -> siguiente = NULL;                                                       // Se pierde su anterior referencia
    }
    else                                                                                // Hay que buscar en los nodos siguientes
    {
        NODO* acomodador = (NODO*) malloc(sizeof(NODO));                                // Nodo que nos ayudara a encontrar nuestro espacio
        NODO* guarda_asientos = (NODO*) malloc(sizeof(NODO));                           // Nodo que nos ayudara a guardar una posicion
        
        acomodador = lista -> inicio -> siguiente;                                      // Se inicia en el segundo nodo
        guarda_asientos = lista -> inicio;                                              // Se inicia en el primer nodo

        while (nodo -> inicio > acomodador -> inicio)                                   // Mientras el inicio del nodo sea mayor que el nodo en la lista
        {
            guarda_asientos = guarda_asientos -> siguiente;                             // guarda_asientos toma el nuevo lugar al que sabemos que el nodo es mayor
            acomodador = acomodador -> siguiente;                                       // Acomodador pasa al siguiente nodo

            if (acomodador == NULL)                                                     // Cuando llegamos al fin de la lista...
                break;                                                                  // ... terminamos el ciclo
        };

        guarda_asientos -> siguiente = nodo;                                            // guarda_asientos apunta a nodo para incluirlo en la cadena
        nodo -> siguiente = acomodador;                                                 // nodo apunta al acomodador para terminar su inclusion

        free(acomodador);
        free(guarda_asientos);
        acomodador = guarda_asientos = NULL;                                            // Ambos nodos pierders sus referencias y su espacio es liberado
    }
};

/* ------ Conclusiones 

Espadas:
    

Genaro:
    

*/