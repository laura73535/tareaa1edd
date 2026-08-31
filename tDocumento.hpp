#ifndef TPARRAFO_HPP
#define TPARRAFO_HPP
#include "tParrafo.hpp"



struct tNodoParrafo
{
    tNodoParrafo* ant;
    tNodoParrafo* sig;
    int id_parrafo;
    tParrafo info;
};

struct tDocumento
{
    tNodoParrafo* head;
    tNodoParrafo* tail;
    int totalParrafos;
};


#endif