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

/*****
* void reflowInsertar
******
* Propaga el exceso de caracteres (mayor a 30) hacia la siguiente linea.
* Crea una nueva linea al final si es estrictamente necesario.
******
* Input:
* tParrafo &parrafo       : Referencia al parrafo
* tNodoLinea* nodoActual  : Nodo desde donde evaluar el desborde
* Returns: void
*****/
void reflowInsertar(tParrafo &parrafo, tNodoLinea* nodoActual) {
    // Mientras haya desborde, iteramos en cascada hacia adelante
    while (nodoActual != nullptr && nodoActual->info.listSize > 30) {
        int cantidadExcedente = nodoActual->info.listSize - 30;
        
        // 1. Extraemos los caracteres sobrantes (desde el indice 30 en adelante)
        char* bufferExcedente = new char[cantidadExcedente];
        for (int i = 0; i < cantidadExcedente; i++) {
            bufferExcedente[i] = nodoActual->info.listArray[30 + i];
        }
        
        // 2. Ajustamos el tamano logico de la linea actual a 30 exactos
        nodoActual->info.listSize = 30;
        
        // 3. Verificamos si existe una linea siguiente, si no, la creamos
        if (nodoActual->sig == nullptr) {
            tNodoLinea* nuevoNodo = new tNodoLinea;
            inicializarLista(nuevoNodo->info, 30); // Capacidad inicial
            
            parrafo.cantLineas++;
            nuevoNodo->nro_linea_parrafo = parrafo.cantLineas;
            nuevoNodo->sig = nullptr;
            
            // Lo enlazamos al final de la lista del parrafo
            nodoActual->sig = nuevoNodo;
            parrafo.tailLinea = nuevoNodo;
        }
        
        tNodoLinea* nodoSiguiente = nodoActual->sig;
        
        // 4. Empujamos (push) el excedente al inicio (indice 0) de la linea siguiente
        // Insertamos de atras hacia adelante para que el orden final sea correcto
        for (int i = cantidadExcedente - 1; i >= 0; i--) {
            insertarCaracter(nodoSiguiente->info, 0, bufferExcedente[i]);
        }
        
        delete[] bufferExcedente; // Evitamos fugas de memoria
        
        // 5. Avanzamos al siguiente nodo; el bucle revisara si este ahora se desborda
        nodoActual = nodoSiguiente;
    }
}

/*****
* void reflowBorrar
******
* Jala caracteres de la linea siguiente si la actual tiene menos de 30.
* Si la linea siguiente queda vacia, la elimina de la lista.
******
* Input:
* tParrafo &parrafo       : Referencia al parrafo
* tNodoLinea* nodoActual  : Nodo desde donde evaluar el deficit
* Returns: void
*****/
void reflowBorrar(tParrafo &parrafo, tNodoLinea* nodoActual) {
    // Mientras falten caracteres y exista una linea abajo de donde jalar
    while (nodoActual != nullptr && nodoActual->info.listSize < 30 && nodoActual->sig != nullptr) {
        int caracteresFaltantes = 30 - nodoActual->info.listSize;
        tNodoLinea* nodoSiguiente = nodoActual->sig;
        
        // Calculamos cuantos podemos tomar (no podemos tomar mas de lo que tiene la linea abajo)
        int caracteresATomar = (nodoSiguiente->info.listSize < caracteresFaltantes) ? 
                                nodoSiguiente->info.listSize : caracteresFaltantes;
        
        // 1. Extraemos caracteres del inicio de la linea siguiente y rellenamos la actual[cite: 1]
        for (int i = 0; i < caracteresATomar; i++) {
            // Usamos la funcion borrarCaracter que ya armamos (extrae del inicio y desplaza todo)
            char charJalado = borrarCaracter(nodoSiguiente->info, 0); 
            // Lo insertamos al final de la linea actual
            insertarCaracter(nodoActual->info, nodoActual->info.listSize, charJalado); 
        }
        
        // 2. Si la linea siguiente se quedo sin caracteres, la destruimos[cite: 1]
        if (nodoSiguiente->info.listSize == 0) {
            // Desacoplamos el nodo de la lista
            nodoActual->sig = nodoSiguiente->sig;
            
            // Si era la ultima linea, actualizamos la cola del parrafo
            if (nodoSiguiente == parrafo.tailLinea) {
                parrafo.tailLinea = nodoActual;
            }
            
            // Liberamos la memoria de la linea vacia[cite: 1]
            liberarLista(nodoSiguiente->info);
            delete nodoSiguiente;
            parrafo.cantLineas--;
            
            // Actualizamos los indices nro_linea_parrafo de las lineas restantes
            tNodoLinea* temp = nodoActual->sig;
            int nuevoNro = nodoActual->nro_linea_parrafo + 1;
            while(temp != nullptr){
                temp->nro_linea_parrafo = nuevoNro++;
                temp = temp->sig;
            }
        }
        
        // Si ya rellenamos los 30 caracteres, avanzamos a la siguiente linea
        // para verificar si a esa le faltan (el efecto cascada).
        if (nodoActual->info.listSize == 30) {
            nodoActual = nodoActual->sig;
        }
    }
}