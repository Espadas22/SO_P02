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
void colocarEnMemoria(int idProceso, int tam);                                          // Asigna memoria a un nuevo proceso

LISTA* crearLista();                                                                    // Reserva la memoria para una nueva lista
int esVacia(LISTA* lista);                                                              // Determina si una lista es vacia
void vaciarAreasLibres ();                                                              // Libera el espacio de las listas del vector
void vaciarLista(LISTA* lista);                                                         // Elimina todos los nodos de una lista
void generarListas();                                                                   // Genera las listas vacias para el vector de areas libres
void imprimirLista(LISTA* lista);                                                       // Imprime todos los nodos (areas libres) de una lista

NODO* crearNodo(int inicio, int fin, NODO* siguiente);                                  // Genera un nuevo nodo
void enlistar(LISTA* lista, NODO* nodo);                                                // Agrega un nodo a una lista
void borrarNodo(LISTA* lista, int nodoInicio);                                          // Borra un nodo de una lista
void dividirNodo(int tam);                                                              // Divide la lista del tamaño indicado


/* Prototipos Hector */



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
        printf("   %d\t\t  ", i);                                                       // Imprime la dirección de memoria

        if (memoriaReal[i] != 0)                                                        // Si esta ocupada, imprime el proceso que la utiliza
            printf("%3d", memoriaReal[i]);                                  
        else
            printf("---");                                                              // Si esta vacia no imprime nada

        if (i > 8)                                                                      // Comienza a imprimir el vector de areas libres
        {
            if (i == 9)
            {
                printf("\t\t\tVector de areas libres");                                 // Imprime el encabezado
            }
            else if  (i == 10)                                                          
            {
                printf("\t\tTamanios\tGrupos disponibles");                             // Imprime las columnas
            }
            else
            {
                imprimirLista(areasLibres[j]);                                          // Imprime la lista correspondiente al vector
                j++;                                                                    // Aumenta a la proxima lista
            }
        } 
            
        printf("\n");                                                                   // Coloca el salto de renglon
    }
}

void ejecutarArchivo()
{
    /* Defineme prro */
};

void resetarMemorias()                                                                  // Funcion usada para regresar la memoria a los valores de inicio
{
    vaciarAreasLibres();                                                                // Liberamos las listas actuales
    generarListas();                                                                    // Creamos las listas nuevas
};

void colocarEnMemoria(int idProceso, int tam)                                           // Coloca en memoria un proceso
{

};

LISTA* crearLista(int tam)                                                              // Recibe el tamaño de las areas de la lista
{
    LISTA* nueva_lista = (LISTA*) malloc(sizeof(LISTA));                                // Reserva el espacio
    nueva_lista -> inicio = NULL;                                                       // No asigna inicio
    nueva_lista -> tam = tam;                                                           // Asigna el tamaño        
    return nueva_lista;                                                                 // Devuelve la direccion
};

void generarListas()
{
    for (int i = 0; i < 16; ++i)                                                        // Llena el vector de areas libres y la memoria real
    {
        if (i < 5)
            areasLibres[i] = crearLista(pow(2,i));                                      // Crea la lista segun la potencia correspondiente
        
        memoriaReal[i] = 0;                                                             // Coloca los valores de inicio en la memoria real
    }

    NODO* primer_bloque = crearNodo(0, 15, NULL);                                       // Creamos el primer bloque de memoria
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
        NODO* corredor = lista -> inicio;                                               // Nodo usado para recorrer la lista
        
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
};

NODO* crearNodo(int inicio, int fin, NODO* siguiente)                                   // Se reciben los parámetros
{
    NODO* nuevo_nodo  = (NODO*) malloc(sizeof(NODO));                                   // Se reserva la memoria
    nuevo_nodo -> inicio = inicio;                                                      // Se asignan los valores correspondientes
    nuevo_nodo -> fin = fin;
    nuevo_nodo -> siguiente = siguiente;
    return nuevo_nodo;                                                                  // Se devuelve la direccion de nodo
};

void borrarNodo(LISTA* lista, int nodoInicio)                                           // Elimina un nodo de una lista
{
    if (esVacia(lista))
        printf("\nLista no tiene elementos\n");                                         // Notifica si la lista es vacía
    else if (lista -> inicio -> inicio == nodoInicio)                                    // El primer nodo es el buscado                                    
    {
        NODO* meseek = lista -> inicio;                                                 // Declaramos un nodo suicida
        
        lista -> inicio = meseek -> siguiente;                                          // Se desplaza el inicio al siguiente (Puede ser NULL)
        
        meseek -> siguiente = NULL;                                                     // Eliminamos su referencia a la lista
        free(meseek);                                                                   // Liberamos el espacio del nodo 
        meseek = NULL;                                                                  // Eliminamos su refrencia apuntada
    }
    else if (lista -> inicio -> siguiente != NULL)                                      // El primer elemento no es el buscado, pero hay mas
    {
        NODO* localizador = lista -> inicio -> siguiente;                               // Nodo que nos ayudara a encontrar la posicion buscada
        NODO* reemplazo = lista -> inicio;                                              // Nodo auxiliar en la eliminacion

        while(localizador != NULL)                                                      // Recorre la lista hasta llegar al final
        {
            if (localizador -> inicio == nodoInicio)                                     // Cuando se localiza el nodo a borrar
            {
                reemplazo -> siguiente = localizador -> siguiente;                      // Se omite el nodo localizado de la lista
                localizador -> siguiente = NULL;                                        // Localizador pierde su referencia a lista
                free(localizador);                                                      // Se libera el espacio ocupado por el nodo
                localizador = reemplazo = NULL;                                         // Ambos nodos pierden sus referencias
                return;                                                                 // La funcion finaliza
            }
            else                                                                        // Cuando no coinciden, se avanza a las siguientes posiciones
            {
                localizador = localizador -> siguiente;
                reemplazo = reemplazo -> siguiente;
            }
        };

        printf("\nLa lista no cuenta con ese nodo\n");                                  // Se notifica que no se enocntro
    };
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
        NODO* acomodador = lista -> inicio -> siguiente;                                // Nodo que nos ayudara a encontrar nuestro espacio
        NODO* guarda_asientos = lista -> inicio;                                        // Nodo que nos ayudara a guardar una posicion

        while (nodo -> inicio > acomodador -> inicio)                                   // Mientras el inicio del nodo sea mayor que el nodo en la lista
        {
            guarda_asientos = guarda_asientos -> siguiente;                             // guarda_asientos toma el nuevo lugar al que sabemos que el nodo es mayor
            acomodador = acomodador -> siguiente;                                       // Acomodador pasa al siguiente nodo

            if (acomodador == NULL)                                                     // Cuando llegamos al fin de la lista...
                break;                                                                  // ... terminamos el ciclo
        };

        guarda_asientos -> siguiente = nodo;                                            // guarda_asientos apunta a nodo para incluirlo en la cadena
        nodo -> siguiente = acomodador;                                                 // nodo apunta al acomodador para terminar su inclusion

        acomodador = guarda_asientos = NULL;                                            // Ambos nodos pierden sus referencias
    }
};

void dividirNodo(int tam)                                                               // Recibe el tamaño del nodo que se quiere dividir
{
    if (tam == 1)                                                                       // Cuando se solitica dividir un area con valor 1
    {
        printf("Las particiones individuales no puede ser divididas\n");                // Notifica que no es posible dividr
    }
    else if (tam == 32)                                                                 // Se sobrepasan los grupos de 16
    {
        printf("\nNo hay bloques divisibles para este tamanio\n");                      // Se notifica que no hay bloques para dividir
        return;                                                                         // La funcion termina
    }
    else                                                                                // El tamaño solicitado es un valor en rango
    {
        int i = 0;                                                                      // Variable auxiliar al conteo

        for ( ; i < 5; ++i)                                                             // Recorremos las areasLibres para encontrar la lista de ese tamaño
        {
            if (areasLibres[i] -> tam == tam)                                           // Cuandos se encuentra la coincidencia
            {
                break;                                                                  // Salimos del ciclo for
            };
        };

        if (areasLibres[i] -> inicio == NULL)                                           // Si la lista esta vacia, se solicita al siguiente tamaño una particion
            dividirNodo(tam*2);
        else                                                                            // Hay al menos una particion disponible
        {
            // Se crean los nuevos nodos para colocar en la lista
            NODO* nodoIzquierdo = crearNodo(areasLibres[i] -> inicio -> inicio, (areasLibres[i] -> inicio -> inicio + tam/2) - 1, NULL);
            NODO* nodoDerecho = crearNodo((areasLibres[i] -> inicio -> inicio + tam/2), (areasLibres[i] -> inicio -> inicio + tam) - 1, NULL); 

            // Se mandan a la ista en orden para falicitar su agregamiento
            enlistar(areasLibres[i-1], nodoDerecho);
            enlistar(areasLibres[i-1], nodoIzquierdo);

            // Se elimina el nodo original divido
            borrarNodo(areasLibres[i], areasLibres[i] -> inicio -> inicio);
        }

    };

};

/*****************         Funciones Hector





********************************************************/

/* ------ Conclusiones 

Espadas:
    

Genaro:
    

*/