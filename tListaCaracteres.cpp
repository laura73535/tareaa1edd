#include "tListaCaracteres.hpp"

/*****
* void inicializarLista
******
* Inicializa los atributos del arreglo dinamico y reserva la memoria inicial.
******
* Input:
* tListaCaracteres &lista : Referencia a la lista a inicializar
* int capacidadInicial    : Tamano inicial del arreglo
* Returns: void
*****/
void inicializarLista(tListaCaracteres &lista, int capacidadInicial) {
    lista.maxSize = capacidadInicial;
    lista.listSize = 0;
    lista.curr = 0; // El indice es 0-indexado
    
    // Reservamos la memoria dinamica usando 'new'
    lista.listArray = new char[lista.maxSize];
}

/*****
* void insertarCaracter
******
* Inserta un caracter en una posicion especifica, desplazando los elementos.
* Si el arreglo se llena, duplica su capacidad.
******
* Input:
* tListaCaracteres &lista : Referencia a la lista
* int pos                 : Posicion donde insertar
* char c                  : Caracter a insertar
* Returns: void
*****/
void insertarCaracter(tListaCaracteres &lista, int pos, char c) {
    // 1. Verificamos si necesitamos duplicar la capacidad
    if (lista.listSize == lista.maxSize) {
        int nuevaCapacidad = lista.maxSize * 2; // Duplicamos el tamano[cite: 1]
        char* nuevoArreglo = new char[nuevaCapacidad];
        
        // Copiamos los datos al nuevo bloque de memoria
        for (int i = 0; i < lista.listSize; i++) {
            nuevoArreglo[i] = lista.listArray[i];
        }
        
        // Liberamos la memoria del arreglo viejo para evitar fugas (memory leaks)[cite: 1]
        delete[] lista.listArray;
        
        // Actualizamos los punteros y la capacidad
        lista.listArray = nuevoArreglo;
        lista.maxSize = nuevaCapacidad;
    }
    
    // 2. Desplazamos los elementos hacia la derecha para hacer espacio
    // Empezamos desde el final hasta la posicion de insercion
    for (int i = lista.listSize; i > pos; i--) {
        lista.listArray[i] = lista.listArray[i - 1];
    }
    
    // 3. Insertamos el nuevo caracter y aumentamos el tamano logico
    lista.listArray[pos] = c;
    lista.listSize++;
}

/*****
* char borrarCaracter
******
* Elimina el caracter en la posicion dada y desplaza los elementos restantes.
******
* Input:
* tListaCaracteres &lista : Referencia a la lista
* int pos                 : Posicion a borrar
* Returns: char, el caracter que fue eliminado
*****/
char borrarCaracter(tListaCaracteres &lista, int pos) {
    // Guardamos el caracter que vamos a borrar para retornarlo
    char caracterBorrado = lista.listArray[pos];
    
    // Desplazamos los elementos hacia la izquierda para tapar el hueco
    for (int i = pos; i < lista.listSize - 1; i++) {
        lista.listArray[i] = lista.listArray[i + 1];
    }
    
    lista.listSize--;
    return caracterBorrado;
}

/*****
* void concatenarTexto
******
* Agrega una cadena de texto al final de la lista actual.
******
* Input:
* tListaCaracteres &lista : Referencia a la lista
* const char* texto       : Arreglo de caracteres a concatenar
* int len                 : Longitud del texto a concatenar
* Returns: void
*****/
void concatenarTexto(tListaCaracteres &lista, const char* texto, int len) {
    // Aprovechamos la funcion que ya hicimos, insertando al final (listSize)
    for (int i = 0; i < len; i++) {
        insertarCaracter(lista, lista.listSize, texto[i]);
    }
}

/*****
* void liberarLista
******
* Libera la memoria dinamica ocupada por el arreglo para evitar memory leaks.
******
* Input:
* tListaCaracteres &lista : Referencia a la lista a limpiar
* Returns: void
*****/
void liberarLista(tListaCaracteres &lista) {
    // Usamos delete[] porque reservamos un arreglo con new[]
    delete[] lista.listArray;
    lista.listArray = nullptr; // Buena practica: apuntar a nulo tras liberar
    lista.listSize = 0;
    lista.maxSize = 0;
}