#ifndef TLISTACARACTERES_HPP
#define TLISTACARACTERES_HPP
#include "tListaCaracteres.hpp"


struct tNodoLinea{
    tNodoLinea* sig;
    int nro_linea_parrafo;
    tListaCaracteres info;
};

struct tParrafo
{
    tNodoLinea* headLinea;
    tNodoLinea* tailLinea;
    int cantLineas;
    int idParrafo; 
};


#endif