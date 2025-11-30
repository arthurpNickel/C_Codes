/* Definição das funções de inicialização da simulação */

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

/*Inicializa o mundo, seus campos e atributos
 **/
void inicializa_mundo(Tp_Mundo *m);

/*Inicializa os heróis e seus atributos
 **/
void inicializa_herois(Tp_Mundo *m);

/*Inicializa as bases e seus campos
 **/
void inicializa_bases(Tp_Mundo *m);

/*Inicializa as missões e seus campos
 **/
void inicializa_missoes(Tp_Mundo *m);

#endif