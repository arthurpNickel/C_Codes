/* Estrutura da entidades da simulação */

#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

#include "valores_simulacao.h"

struct Heroi 
{
	int id;
	struct cjto_t *habilidades;
	int paciencia;
	int velocidade;
	int xp;
	int base;
	int vivo; /* 1 se herói está vivo, 0 se morto */
} ;

struct Coord 
{
	int x;
	int y;
} ;

struct Base 
{
	int id;
	int lotacao; 
	struct cjto_t *presentes; /* Conjunto de IDs dos heróis presentes na base */
	struct fila_t *fila_espera; /* Fila de heróis esperando para entrar na base */
	struct Coord local;
	int fila_max; /* Guarda o tamanho da maior fila que base teve na simulação */
	int num_missoes; /* Guarda a quantidade de missões em que a base se envolveu */
} ;


struct Missao 
{
	int id;
	struct cjto_t *habilidades_m; /* Conjunto de habilidades requeridas */
	struct Coord local;
	int tempo;
	int tentativas; /* Número de tentativas realizadas para a missão */
} ;

struct Mundo 
{
	int nherois;
	struct Heroi herois[NHEROIS];
	int nbases;
	struct Base bases[NBASES];
	int nmissoes;
	struct Missao **missoes; /* Missões alocadas dinamicamente */
	int nhabilidades;
	int ncompostos;
	int neventos; /* Guarda quantidade de eventos tratados na simulação */

	struct Coord tam_mundo;
	int relogio;
	struct fprio_t *LEF;
} ;

/* Nomenclatura das estruturas das entidades */
typedef struct Heroi Tp_Heroi;
typedef struct Base Tp_Base;
typedef struct Missao Tp_Missao;
typedef struct Mundo Tp_Mundo;

#endif