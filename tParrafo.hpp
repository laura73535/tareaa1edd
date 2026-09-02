#ifndef TPARRAFO_HPP
#define TPARRAFO_HPP

#include "tListaCaracteres.hpp"

// Estructura del nodo de linea 
struct tNodoLinea {
    tNodoLinea* sig;           // Unicamente enlace hacia adelante
    int nro_linea_parrafo;     // Indice de la linea
    tListaCaracteres info;     // Los datos del Nivel 1[cite: 1]
};

// Estructura del TDA Segundo Nivel: tParrafo
struct tParrafo {
    tNodoLinea* headLinea;     // Puntero al inicio de la lista[cite: 1]
    tNodoLinea* tailLinea;     // Puntero al final de la lista[cite: 1]
    int cantLineas;            // Cantidad total de lineas[cite: 1]
    int id_parrafo;            // Identificador unico del parrafo
};

// Firmas de las funciones del TDA[cite: 1]
void inicializarParrafo(tParrafo &parrafo, int idParrafo);
void agregarLineaAlFinal(tParrafo &parrafo, const tListaCaracteres &linea);
void fusionarLineas(tParrafo &parrafo, int nroL1, int nroL2);
void reflowInsertar(tParrafo &parrafo, tNodoLinea* nodoActual);
void reflowBorrar(tParrafo &parrafo, tNodoLinea* nodoActual);
void liberarParrafo(tParrafo &parrafo);

#endif