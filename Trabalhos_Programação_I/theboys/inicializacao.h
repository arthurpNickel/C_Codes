#ifndef INICIALIZACAO_H
#define INICIALIZACAO_H

#include <stdio.h>
#include <stdlib.h>

#include "valores_simulacao.h"
#include "entidades.h"

#include "fprio.h"
#include "conjunto.h"
#include "fila.h"
#include "auxiliares.h"

/* Inicializações */
void inicializa_mundo(Tp_Mundo *m);


void inicializa_herois(Tp_Mundo *m);


void inicializa_bases(Tp_Mundo *m);


void inicializa_missoes(Tp_Mundo *m);

#endif