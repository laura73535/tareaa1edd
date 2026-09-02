#include "tParrafo.hpp"

/*****
* void inicializarParrafo
******
* Inicializa los punteros y contadores de la lista enlazada simple.
******
* Input:
* tParrafo &parrafo : Referencia al parrafo
* int idParrafo     : ID que se le asignara al parrafo
* Returns: void
*****/
void inicializarParrafo(tParrafo &parrafo, int idParrafo) {
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
    parrafo.id_parrafo = idParrafo;
}

/*****
* void agregarLineaAlFinal
******
* Crea un nuevo nodo de linea y lo enlaza al final del parrafo (append natural).
******
* Input:
* tParrafo &parrafo             : Referencia al parrafo
* const tListaCaracteres &linea : Linea a copiar e insertar
* Returns: void
*****/
void agregarLineaAlFinal(tParrafo &parrafo, const tListaCaracteres &linea) {
    // 1. Instanciamos el nuevo nodo en memoria dinamica
    tNodoLinea* nuevoNodo = new tNodoLinea;
    
    // 2. COPIA PROFUNDA: Inicializamos la lista interna y copiamos los caracteres
    // Esto es vital para no compartir punteros de arreglos entre diferentes TDAs.
    inicializarLista(nuevoNodo->info, linea.maxSize);
    concatenarTexto(nuevoNodo->info, linea.listArray, linea.listSize);
    
    // 3. Configuramos los atributos del nodo
    parrafo.cantLineas++;
    nuevoNodo->nro_linea_parrafo = parrafo.cantLineas;
    nuevoNodo->sig = nullptr; // Como va al final, apunta a nulo
    
    // 4. Enlazamos el nodo en la lista
    if (parrafo.headLinea == nullptr) { // Si la lista esta vacia
        parrafo.headLinea = nuevoNodo;
        parrafo.tailLinea = nuevoNodo;
    } else { // Si ya hay nodos, lo conectamos a la cola actual
        parrafo.tailLinea->sig = nuevoNodo;
        parrafo.tailLinea = nuevoNodo;
    }
}

/*****
* void liberarParrafo
******
* Recorre la lista simplemente enlazada liberando cada linea y luego cada nodo.
******
* Input:
* tParrafo &parrafo : Referencia al parrafo a destruir
* Returns: void
*****/
void liberarParrafo(tParrafo &parrafo) {
    tNodoLinea* actual = parrafo.headLinea;
    
    while (actual != nullptr) {
        tNodoLinea* siguiente = actual->sig; // Guardamos el enlace al siguiente
        
        // Liberamos primero el arreglo dinamico interno de la linea
        liberarLista(actual->info); 
        
        // Luego liberamos el nodo de la lista enlazada
        delete actual; 
        
        actual = siguiente; // Avanzamos
    }
    
    // Reseteamos el TDA
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}