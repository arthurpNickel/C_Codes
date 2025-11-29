#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

#include "valores_simulacao.h"

//Tudo são inteiros iguais ou maiores que zero
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
	int lotacao; //número máximo de heróis

	//Assim será????
	struct cjto_t *presentes; //conjunto de IDs dos heróis presentes na base

	//verificar se é fila ou lista!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	struct fila_t *fila_espera; //fila de heróis esperando para entrar na base -> é uma fila normal

	struct Coord local;
	
	int fila_max; /* Guarda o tamanho da maior fila que simulação teve*/

	int num_missoes; /* Guarda a quantidade de missões em que herois da base se envolveram */
} ;


struct Missao 
{
	int id;
	struct cjto_t *habilidades_m; //conjunto de habilidades necessárias
	struct Coord local;
	int tempo; //Não tenho certeza disso!!!!!!!!!!!!!!!!!!]
	int tentativas; //posso??!!!!!!!!!!!!!!!!!!!!!
} ;

struct Mundo 
{
	int nherois;
	struct Heroi herois[NHEROIS]; //Número constante assim mesmo?
	int nbases;
	struct Base bases[NBASES]; //revisar isso
	int nmissoes;
	struct Missao **missoes; //revisar isso
	int nhabilidades;
	int ncompostos; //Compostos V!!!!!!!!!!
	int neventos; /* Guarda quantidade de eventos tratados */

	//T: Não precisa desse campo-> Só verificar quantas estão na LEF ainda!!!!!!!!!!!!!!!! 
	int ncumpridas; /* Guarda quantidade de missões cumpridas */
	struct Coord tam_mundo;
	int relogio;
	struct fprio_t *LEF;
} ;

typedef struct Heroi Tp_Heroi;
typedef struct Base Tp_Base;
typedef struct Missao Tp_Missao;
typedef struct Mundo Tp_Mundo;

#endif