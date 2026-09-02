#ifndef TLISTACARACTERES_HPP
#define TLISTACARACTERES_HPP

// Estructura del arreglo dinamico para los caracteres
struct tListaCaracteres {
    char* listArray; // Puntero al arreglo en memoria dinamica
    int listSize;    // Longitud actual de la linea
    int maxSize;     // Capacidad maxima del arreglo
    int curr;        // Indice del cursor interno
};

// Firmas de las funciones del TDA
void inicializarLista(tListaCaracteres &lista, int capacidadInicial);
void insertarCaracter(tListaCaracteres &lista, int pos, char c);
char borrarCaracter(tListaCaracteres &lista, int pos);
void concatenarTexto(tListaCaracteres &lista, const char* texto, int len);
void liberarLista(tListaCaracteres &lista);

#endif