/* Definição das funções auxiliares da simulação */

#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "entidades.h"

#include "conjunto.h"

/*Retorna um número aleatório entre min e max, inclusive
 **/
int aleatorio(int min, int max);

/*Retorna união das habilidades entre u (onde será unido) e h
 **/
struct cjto_t *uniao_habilidades(struct cjto_t *u, struct cjto_t *h);

/*Função de troca
 **/
void troca(int *a, int *b);

/*Calcula distância entre duas bases
 **/
int calcula_distancia_bases(Tp_Mundo *m, int b1, int b2);

/*Calcula distância da missão até a base
 **/
int calcula_distancia_missao(Tp_Mundo *m, Tp_Missao *M, int id_base);

/*Algoritmo de ordenação QuickSort
 **/
void quick_sort(Tp_Mundo *m, Tp_Missao *M, int v[], int ini, int fim);

#endif