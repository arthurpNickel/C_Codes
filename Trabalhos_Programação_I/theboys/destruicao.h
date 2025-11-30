/* Definição das funções de destruição da simulação */

#ifndef DESTRUICAO_H
#define DESTRUICAO_H

#include <stdio.h>
#include <stdlib.h>

#include "entidades.h"
#include "valores_simulacao.h"

#include "fprio.h"
#include "conjunto.h"
#include "fila.h"

/*Destruição dos conjuntos de presentes e das filas de espera de todas as bases
 **/
void destroi_bases(Tp_Mundo *m);

/*Destruição do conjunto de habilidade de todas as missões e de todas as missões cumpridas
 **/
void destroi_missoes(Tp_Mundo *m);

/*Destruição dos conjuntos de habilidades dos heróis
 **/
void destroi_herois(Tp_Mundo *m);

/*Destruição da LEF da simulação e de todos os eventos restantes nela
 **/
void destroi_lef(Tp_Mundo *m);

#endif